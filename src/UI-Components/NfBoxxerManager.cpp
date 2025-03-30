//
//  NfBoxxerManager.cpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 26.02.24.
//

#include "NfBoxxerManager.hpp"

namespace nfUI {

void NfBoxxerManager::addBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue) {
    auto newBoxxer = std::make_shared<NfBoxxer>(config, name, std::move(initialValue));
    boxxers.push_back(newBoxxer);
}

void NfBoxxerManager::drawBoxxers() {
    for (auto& boxxer : boxxers) {
        boxxer->draw(); // Call the draw method of each Boxxer
    }
}

bool NfBoxxerManager::removeBoxxerByName(const std::string& name) {
    auto it = std::find_if(boxxers.begin(), boxxers.end(),
                           [&name](const std::shared_ptr<NfBoxxer>& boxxer) { return boxxer->_name == name; });
    if (it != boxxers.end()) {
        boxxers.erase(it);
        return true; // Successfully removed
    }
    return false; // Element not found
}

} // namespace nfUI
