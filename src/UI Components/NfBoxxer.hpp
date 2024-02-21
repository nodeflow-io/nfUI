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

    // Constructor to take a NfUIConfig reference and name
    // Updated constructor
    // Updated constructor
    NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue)
            : NfUIElement(config, std::move(initialValue), name), // Assuming NfUIElement has a matching constructor
              _config(config), _name(name) {
            // Your initialization code here
        }
    
    
    void draw() {
        if (_firstRender) {
            std::cout << "First render of " << _name << std::endl;
            NFValue* valueRawPtr = this->getValue();
            if (valueRawPtr != nullptr) {
                std::string valueAsString = valueRawPtr->toString();
                std::cout << "Value as string: " << valueAsString << std::endl;
            } else {
                std::cout << "No value available." << std::endl;
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

            // Translate the drawing context down by the vertical offset for each child
            ofTranslate(0, verticalOffset);
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
        }
        // After the first render, set the flag to false
        if (_firstRender) {
            _firstRender = false;
        }
    }

    
    void drawold()  {
        // Use the colors and dimensions from the config
        ofSetColor(_config.backgroundColor);
        ofDrawRectangle(_config.bounds); // Use the bounds from the config

        // Move the drawing context to the rectangle's position for drawing children
        ofPushMatrix();
        ofTranslate(_config.bounds.getPosition());
        for (auto& child : children) {
            child->draw(); // Recursively draw each child
        }

        
        ofPopMatrix();
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
