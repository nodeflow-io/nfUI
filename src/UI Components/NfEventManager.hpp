//
//  NfEventManager.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmiaer on 02.03.24.
//

#ifndef NfEventManager_hpp
#define NfEventManager_hpp

#include <functional>
#include <map>
#include <string>
#include <vector>
namespace nfUI {

class NfEventManager {
public:
    using EventListener = std::function<void(const std::string&)>;
    using ListenerID = size_t; // Unique identifier for listeners

private:
    std::map<std::string, std::map<ListenerID, EventListener>> listeners;
    ListenerID nextID = 0; // Counter to generate unique IDs for new listeners

public:
    // Subscribe and return a unique ListenerID
    ListenerID subscribe(const std::string& eventType, EventListener listener) {
        ListenerID id = nextID++;
        listeners[eventType][id] = listener;
        return id; // Return the ID so it can be used to unsubscribe
    }
    
    // Unsubscribe using the listener's unique ID
    void unsubscribe(const std::string& eventType, ListenerID id) {
        if (listeners.find(eventType) != listeners.end()) {
            listeners[eventType].erase(id);
        }
    }

    void emit(const std::string& eventType, const std::string& eventData) {
        if (listeners.find(eventType) != listeners.end()) {
            for (auto& pair : listeners[eventType]) {
                pair.second(eventData); // pair.second is the EventListener
            }
        }
    }
};


// Declaration only
extern NfEventManager g_eventManager;

}




#endif /* NfEventManager_hpp */
