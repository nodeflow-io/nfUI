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
public:
    std::string _name;
    NfUIConfig _config; // Reference to a NfUIConfig object

    // Constructor to take a NfUIConfig reference and name
    NfBoxxer(NfUIConfig& config, const std::string& name)
    : _config(config), _name(name) {}

    void draw() {
        ofSetColor(_config.backgroundColor);
        ofDrawRectangle(_config.bounds); // Draw the current element

        float verticalOffset = _config.bounds.y + _config.marginTop + _config.paddingTop;

        for (auto& child : children) {
            auto& childConfig = child->_config; // Assuming each child also has a _config
            
            // Calculate the child's absolute position based on the parent's offset
            childConfig.bounds.y = verticalOffset + childConfig.marginTop;

            // Draw the child
            child->draw();

            // Update the verticalOffset for the next child
            // Include the current child's height, bottom margin, and padding
            verticalOffset += childConfig.height + childConfig.marginBottom + _config.paddingBottom;
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
