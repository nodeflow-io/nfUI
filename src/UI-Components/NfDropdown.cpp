//
//  NfDropdown.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 03.03.24.
//

#include "NfDropdown.hpp"

namespace nfUI {

NfDropdown::NfDropdown(const NfUIConfig& config, const std::string& name)
    : NfBoxxer(config, name, std::make_unique<StringNFValue>(""))
{
}

void NfDropdown::selectItem(int itemIndex) {
    // Logic to handle item selection
    nfUI::NfEventManager::getEventManager().emit("dropdown_selection", std::to_string(itemIndex));
    // Close the modal after selection
    // g_nodeManager.closeModalNode(_name);
}

void NfDropdown::draw() {
    // Your drawing logic here
    std::cout << "Drawing dropdown: " << _name << std::endl;
}

} // namespace nfUI
