#pragma once

#include <any>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <memory> // For weak_ptr
#include "ofLog.h"

namespace nfUI {

enum class AppEventType {
    // OpenFrameworks Mouse Events
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

struct Event {
    AppEventType type;
    std::string sourceId = ""; // Optional: ID of the UI element originating the event
    std::any payload;         // Data associated with the event (e.g., button ID, slider value, key code)
    void* sender = nullptr;    // Optional: Raw pointer to sender (use carefully)

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
        // Use weak_ptr to automatically handle object destruction
        // Listener needs to be tied to the lifetime of the subscribing object
        // This example uses a raw function pointer for simplicity,
        // but binding to member functions often requires std::weak_ptr/shared_ptr management.
        // A more robust approach involves storing weak_ptr to the listening object
        // and calling a member function if the object still exists.
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

    // --- Singleton Pattern ---
    static NfEventBus& getInstance();

private:
    // Map event types to a list of subscriptions interested in that type
    std::map<AppEventType, std::vector<Subscription>> subscriptions;
    // Potentially a mutex for thread safety if needed, though oF UI is often single-threaded
    // std::mutex mtx;

    NfEventBus() = default; // Private constructor
    NfEventBus(const NfEventBus&) = delete; // Delete copy constructor
    void operator=(const NfEventBus&) = delete; // Delete assignment operator
};

// Macro for easier access if using singleton
#define BUS nfUI::NfEventBus::getInstance()

} // namespace nfUI

