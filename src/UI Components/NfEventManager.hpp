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
    
private:
    std::map<std::string, std::vector<EventListener>> listeners;
    
public:
    void subscribe(const std::string& eventType, EventListener listener) {
        listeners[eventType].push_back(listener);
    }
    
    void emit(const std::string& eventType, const std::string& eventData) {
        for (auto& listener : listeners[eventType]) {
            listener(eventData);
        }
    }
};

// Global event manager instance
extern NfEventManager g_eventManager;

}




#endif /* NfEventManager_hpp */
