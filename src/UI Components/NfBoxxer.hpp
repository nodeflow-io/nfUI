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

        float verticalOffset = _config.paddingTop; // Start with the top padding as the initial offset

        // Use the parent's position as the starting point
        float parentY = _config.bounds.y + _config.marginTop;

        for (auto& child : children) {
            // No need to modify child->_config.bounds directly
            
            ofPushMatrix(); // Save the current drawing context

            // Translate the drawing context down by the vertical offset for each child
            ofTranslate(0, verticalOffset);

            // Draw the child at the newly translated position
            child->draw();

            // Update the verticalOffset for the next child
            // Include the child's height, its bottom margin, and padding
            verticalOffset += child->_config.height + child->_config.marginBottom + _config.paddingBottom;

            ofPopMatrix(); // Restore the drawing context
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
