//
//  NfDropdown.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 03.03.24.
//

#ifndef NfDropdown_hpp
#define NfDropdown_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfDropdown : public NfBoxxer {
public:
    NfDropdown(const NfUIConfig& config, const std::string& name)
        : NfBoxxer(config, name, std::make_unique<StringNFValue>("")) {}

    void selectItem(int itemIndex) {
        // Convert itemIndex to string
        std::string itemIndexStr = std::to_string(itemIndex);

        // Logic to handle item selection
        // Notify the NfNodeManager or parent node of the selection
        g_eventManager.emit("dropdown_selection", itemIndexStr);
    }

    // Override draw method if needed to render dropdown options
};

}

#endif /* NfDropdown_hpp */
