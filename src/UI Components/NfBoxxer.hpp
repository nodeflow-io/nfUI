//
//  NfBoxxer.hpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 21.02.24.
//

#ifndef NfBoxxer_hpp
#define NfBoxxer_hpp

#include "nfUIElement.hpp"
namespace nfUI {

class NfBoxxer : public NfUIElement {
    
private:
    bool _firstRender = true; // Flag to track if draw() was called for the first time

public:
    std::string _name;
    NfUIConfig _config; // Reference to a NfUIConfig object


    // Updated constructor
    NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue)
            : NfUIElement(config, std::move(initialValue), name), 
              _config(config), _name(name) {
            // Your initialization code here
        }
    
    // this implements the base class
    // put out debug infos like paddings and margins
    void draw() {
        if (_firstRender) {
            std::cout << "Boxxer: First render of " << _name << std::endl;
            NFValue* valueRawPtr = this->getValue();
            if (valueRawPtr != nullptr) {
                std::string valueAsString = valueRawPtr->toString();
                std::cout << "Boxxer: Value as string: " << valueAsString << std::endl;
            } else {
                std::cout << "Boxxer: No value available." << std::endl;
            }
        }
        ofSetColor(_config.backgroundColor);
        ofDrawRectangle(_config.bounds); // Draw the current element

        float verticalOffset = _config.marginTop; // Start with the top padding as the initial offset

        // Use the parent's position as the starting point
        float parentY = _config.bounds.y + _config.marginTop;

        for (auto& child : children) {
            // No need to modify child->_config.bounds directly
            
            ofPushMatrix(); // Save the current drawing context
            if (_firstRender) std::cout << "pushM\n";
            // Translate the drawing context down by the vertical offset for each child
            // ofTranslate(0, verticalOffset);
            // Perform logging only on the first render of each element
            if (_firstRender) {
                std::cout << "  child render of " << child->parameters.getName() << " at vertical offset: " << verticalOffset << std::endl;
            }
            // Draw the child at the newly translated position
            child->draw();

            // Update the verticalOffset for the next child
            // Include the child's height, its bottom margin, and padding
            verticalOffset += child->_config.height + child->_config.marginBottom + _config.paddingBottom;

            ofPopMatrix(); // Restore the drawing context
            if (_firstRender) std::cout << "popM\n";
        }
        // After the first render, set the flag to false
        if (_firstRender) {
            _firstRender = false;
        }
    }

    
    void drawChildren (const float& paddingLeft, const float& paddingRight) {
        ofPushMatrix();
        ofTranslate(paddingLeft, paddingRight);
        for (size_t i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            if (i) {
                auto& lastChild = children[i-1];
                float width, height;
                this->getChildDimensions(lastChild, width, height);
                ofTranslate(0, height);
            }
            child->draw();
        }
        ofPopMatrix();
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
