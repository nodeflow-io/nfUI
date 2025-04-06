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

bool NfDropdown::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                // Handle item selection based on click position
                // For example, determine which item was clicked based on localPoint.y
                int itemIndex = 0; // Replace with actual calculation based on localPoint
                selectItem(itemIndex);
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_MOVED:
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_EXITED:
            if (!boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = false;
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI
