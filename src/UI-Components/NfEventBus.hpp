#pragma once

#include <any>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <memory> // For weak_ptr
#include "ofLog.h"
#include "ofEvents.h"
#include "ofAppRunner.h" // For ofGetWindowPtr

namespace nfUI {

// Map our application events to OF events for consistency
enum class AppEventType {
    // OpenFrameworks Mouse Events - using OF's event structure
    MOUSE_PRESSED,
    MOUSE_RELEASED,
    MOUSE_MOVED,
    MOUSE_DRAGGED,
    MOUSE_SCROLLED,
    MOUSE_ENTERED,
    MOUSE_EXITED,

    // OpenFrameworks Window Events
    WINDOW_RESIZED,
    WINDOW_ENTERED,
    WINDOW_EXITED,

    // OpenFrameworks Keyboard Events
    KEY_PRESSED,
    KEY_RELEASED,

    // UI Component Events
    BUTTON_CLICKED,
    SLIDER_CHANGED,
    CUSTOM_UI_ACTION,
    DATA_UPDATED
};

// Specialized event types for different OF event types
struct Event {
    AppEventType type;
    std::string sourceId = ""; // Optional: ID of the UI element originating the event
    std::any payload;         // Data associated with the event (e.g., button ID, slider value, key code)
    void* sender = nullptr;    // Optional: Raw pointer to sender (use carefully)

    // Converters to/from OF event args
    static Event fromMouseEvent(const ofMouseEventArgs& args, AppEventType type) {
        Event e;
        e.type = type;
        e.payload = args;
        return e;
    }

    static Event fromKeyEvent(const ofKeyEventArgs& args, AppEventType type) {
        Event e;
        e.type = type;
        e.payload = args;
        return e;
    }

    static Event fromResizeEvent(const ofResizeEventArgs& args) {
        Event e;
        e.type = AppEventType::WINDOW_RESIZED;
        e.payload = args;
        return e;
    }

    // Helper template to safely get payload
    template<typename T>
    inline T payload_as() const {
        try {
            return std::any_cast<T>(payload);
        } catch (const std::bad_any_cast& e) {
            // Handle error: log, throw, return default value?
            ofLogError("Event") << "Failed to cast payload for event type " << static_cast<int>(type);
            return T{}; // Return default-constructed T
        }
    }
};

class NfEventBus {
public:
    // Define a filter type: a function that takes an Event and returns true if it passes
    using EventFilter = std::function<bool(const Event&)>;

    // Define a listener type: a function that processes an Event
    using EventListener = std::function<void(const Event&)>;

    // Store listener and its filter together
    struct Subscription {
        EventListener listener;
        EventFilter filter;
        void* owner = nullptr; // Optional: Pointer to the subscribing object for easy unsubscribeAll.
    };

    // Subscribe with a filter
    void subscribe(AppEventType type, EventListener listener, EventFilter filter = nullptr, void* owner = nullptr);
    
    // Convenience subscribe without a filter (matches any event of this type)
    void subscribe(AppEventType type, EventListener listener, void* owner = nullptr);

    // Unsubscribe all listeners owned by a specific object
    void unsubscribeAll(void* owner);

    // Publish an event
    void publish(const Event& event);

    // Setup OF event listeners - now public to be called after OF is initialized
    void setupOFEvents();
    
    // Remove OF event listeners
    void removeOFEvents();

    // --- Singleton Pattern ---
    static NfEventBus& getInstance();

    // Check if OF events are set up
    bool isInitialized() const { return _initialized; }

private:
    // Map event types to a list of subscriptions interested in that type
    std::map<AppEventType, std::vector<Subscription>> subscriptions;
    bool _initialized = false;
    
    // OF Event handlers
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args);
    void mouseEntered(ofMouseEventArgs& args);
    void mouseExited(ofMouseEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void windowResized(ofResizeEventArgs& args);

    NfEventBus() noexcept; // Constructor now defined in CPP file
    ~NfEventBus() noexcept; // Destructor removes OF events if initialized
    NfEventBus(const NfEventBus&) = delete; // Delete copy constructor
    void operator=(const NfEventBus&) = delete; // Delete assignment operator
};

// Macro for easier access if using singleton
#define BUS nfUI::NfEventBus::getInstance()

} // namespace nfUI

