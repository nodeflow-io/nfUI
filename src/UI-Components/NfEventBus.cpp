#include "NfEventBus.hpp"

namespace nfUI {

NfEventBus::NfEventBus() noexcept : _initialized(false) {
    // Constructor now explicitly defined with no actions
}

NfEventBus::~NfEventBus() noexcept {
    if (_initialized) {
        removeOFEvents();
    }
}

void NfEventBus::setupOFEvents() {
    if (_initialized) return;  // Don't set up twice
    
    // Only set up events if OF is initialized (window exists)
    if (ofGetWindowPtr() != nullptr) {
        ofAddListener(ofEvents().mousePressed, this, &NfEventBus::mousePressed);
        ofAddListener(ofEvents().mouseReleased, this, &NfEventBus::mouseReleased);
        ofAddListener(ofEvents().mouseMoved, this, &NfEventBus::mouseMoved);
        ofAddListener(ofEvents().mouseDragged, this, &NfEventBus::mouseDragged);
        ofAddListener(ofEvents().mouseScrolled, this, &NfEventBus::mouseScrolled);
        ofAddListener(ofEvents().mouseEntered, this, &NfEventBus::mouseEntered);
        ofAddListener(ofEvents().mouseExited, this, &NfEventBus::mouseExited);
        ofAddListener(ofEvents().keyPressed, this, &NfEventBus::keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &NfEventBus::keyReleased);
        ofAddListener(ofEvents().windowResized, this, &NfEventBus::windowResized);
        _initialized = true;
    } else {
        ofLogWarning("NfEventBus") << "Attempted to setup events before OF window initialization";
    }
}

void NfEventBus::removeOFEvents() {
    if (!_initialized) return;  // Don't remove if not set up
    
    ofRemoveListener(ofEvents().mousePressed, this, &NfEventBus::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &NfEventBus::mouseReleased);
    ofRemoveListener(ofEvents().mouseMoved, this, &NfEventBus::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &NfEventBus::mouseDragged);
    ofRemoveListener(ofEvents().mouseScrolled, this, &NfEventBus::mouseScrolled);
    ofRemoveListener(ofEvents().mouseEntered, this, &NfEventBus::mouseEntered);
    ofRemoveListener(ofEvents().mouseExited, this, &NfEventBus::mouseExited);
    ofRemoveListener(ofEvents().keyPressed, this, &NfEventBus::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &NfEventBus::keyReleased);
    ofRemoveListener(ofEvents().windowResized, this, &NfEventBus::windowResized);
    _initialized = false;
}

// OF Event handlers that forward to our event bus
void NfEventBus::mousePressed(ofMouseEventArgs& args) {
    if (!_initialized) return;
    // ofLogNotice("NfEventBus") << "Mouse pressed at: " << args.x << "," << args.y;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_PRESSED));
}

void NfEventBus::mouseReleased(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_RELEASED));
}

void NfEventBus::mouseMoved(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_MOVED));
}

void NfEventBus::mouseDragged(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_DRAGGED));
}

void NfEventBus::mouseScrolled(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_SCROLLED));
}

void NfEventBus::mouseEntered(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_ENTERED));
}

void NfEventBus::mouseExited(ofMouseEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromMouseEvent(args, AppEventType::MOUSE_EXITED));
}

void NfEventBus::keyPressed(ofKeyEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromKeyEvent(args, AppEventType::KEY_PRESSED));
}

void NfEventBus::keyReleased(ofKeyEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromKeyEvent(args, AppEventType::KEY_RELEASED));
}

void NfEventBus::windowResized(ofResizeEventArgs& args) {
    if (!_initialized) return;
    publish(Event::fromResizeEvent(args));
}

void NfEventBus::subscribe(AppEventType type, EventListener listener, EventFilter filter, void* owner) {
    // std::lock_guard<std::mutex> lock(mtx); // If thread-safe needed
    if (!filter) {
        // Default filter: always pass if the type matches (already handled by map key)
        filter = [](const Event&){ return true; };
    }
    subscriptions[type].push_back({listener, filter, owner});
}

void NfEventBus::subscribe(AppEventType type, EventListener listener, void* owner) {
    subscribe(type, listener, nullptr, owner);
}

void NfEventBus::unsubscribeAll(void* owner) {
    // std::lock_guard<std::mutex> lock(mtx); // If thread-safe needed
    for (auto& pair : subscriptions) {
        auto& subs = pair.second;
        subs.erase(std::remove_if(subs.begin(), subs.end(),
                   [owner](const Subscription& s) { return s.owner == owner; }),
                   subs.end());
    }
}

void NfEventBus::publish(const Event& event) {
    // std::lock_guard<std::mutex> lock(mtx); // If thread-safe needed
    auto it = subscriptions.find(event.type);
    if (it != subscriptions.end()) {
        // Iterate over a copy in case a listener modifies the subscriptions
        auto listeners_copy = it->second;
        for (const auto& sub : listeners_copy) {
            // Check if the filter passes
            if (sub.filter(event)) {
                // Call the listener
                sub.listener(event);
            }
        }
    }
}

NfEventBus& NfEventBus::getInstance() {
    static NfEventBus instance;
    return instance;
}

} // namespace nfUI 
