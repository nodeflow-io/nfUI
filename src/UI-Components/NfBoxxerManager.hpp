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
    void addBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue);

    // Draw all Boxxer elements managed by this manager
    void drawBoxxers();

    // Remove a Boxxer element by name
    bool removeBoxxerByName(const std::string& name);
};

} // namespace nfUI

#endif /* NfBoxxerManager_hpp */
