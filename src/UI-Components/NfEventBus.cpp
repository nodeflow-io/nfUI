#include "NfEventBus.hpp"

namespace nfUI {

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