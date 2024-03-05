//
//  NfBoxxerManager.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#ifndef NfBoxxerManager_hpp
#define NfBoxxerManager_hpp

#include <vector>
#include <memory>
#include "NfBoxxer.hpp"

namespace nfUI {

class NfBoxxerManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> boxxers;

public:
    // Add a new Boxxer element to the manager
    void addBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue) {
        auto newBoxxer = std::make_shared<NfBoxxer>(config, name, std::move(initialValue));
        boxxers.push_back(newBoxxer);
    }

    // Draw all Boxxer elements managed by this manager
    void drawBoxxers() {
        for (auto& boxxer : boxxers) {
            boxxer->draw(); // Call the draw method of each Boxxer
        }
    }

    // Remove a Boxxer element by name
    bool removeBoxxerByName(const std::string& name) {
        auto it = std::find_if(boxxers.begin(), boxxers.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& boxxer) { return boxxer->_name == name; });
        if (it != boxxers.end()) {
            boxxers.erase(it);
            return true; // Successfully removed
        }
        return false; // Element not found
    }
};

} // namespace nfUI


#endif /* NfBoxxerManager_hpp */
