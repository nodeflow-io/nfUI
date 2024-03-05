//
//  NfEventManager.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#include "NfEventManager.hpp"

namespace nfUI {

NfEventManager& NfEventManager::getEventManager() {
    static NfEventManager instance; // This will only be initialized once
    return instance;
}

NfEventManager::ListenerID NfEventManager::subscribe(const std::string& eventType, EventListener listener) {
    ListenerID id = nextID++;
    listeners[eventType][id] = std::move(listener);
    return id; // Return the ID so it can be used to unsubscribe
}

void NfEventManager::unsubscribe(const std::string& eventType, ListenerID id) {
    if (listeners.find(eventType) != listeners.end()) {
        listeners[eventType].erase(id);
    }
}

void NfEventManager::emit(const std::string& eventType, const std::string& eventData) {
    auto it = listeners.find(eventType);
    if (it != listeners.end()) {
        for (auto& pair : it->second) {
            pair.second(eventData); // pair.second is the EventListener
        }
    }
}

} // namespace nfUI
