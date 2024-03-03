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
        // Logic to handle item selection
        g_eventManager.emit("dropdown_selection", std::to_string(itemIndex));
        // Close the modal after selection
       // g_nodeManager.closeModalNode(_name);
    }

    // Override the draw method to render dropdown options
    void draw() override {
        // Your drawing logic here
        std::cout << "Drawing dropdown: " << _name << std::endl;
    }
};

}

#endif /* NfDropdown_hpp */
