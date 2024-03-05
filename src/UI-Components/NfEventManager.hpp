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
    // Map to hold listeners for different event types
    std::map<std::string, std::map<ListenerID, EventListener>> listeners;
    ListenerID nextID = 0; // Counter to generate unique IDs for new listeners

    // Private constructor for Singleton pattern
    NfEventManager() {}

public:
    // Deleted copy constructor and assignment operator for Singleton pattern
    NfEventManager(const NfEventManager&) = delete;
    NfEventManager& operator=(const NfEventManager&) = delete;

    // Static method to access the Singleton instance
    static NfEventManager& getEventManager();

    // Subscribe and return a unique ListenerID
    ListenerID subscribe(const std::string& eventType, EventListener listener);
    
    // Unsubscribe using the listener's unique ID
    void unsubscribe(const std::string& eventType, ListenerID id);

    // Emit an event to all subscribed listeners
    void emit(const std::string& eventType, const std::string& eventData);
};

} // namespace nfUI




#endif /* NfEventManager_hpp */
