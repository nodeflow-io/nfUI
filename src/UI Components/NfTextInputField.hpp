//
//  NfTextInputField.hpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 22.02.24.
//

#ifndef NfTextInputField_hpp
#define NfTextInputField_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfTextInputField : public NfBoxxer {
    
private:
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset; // font size dependant
    uint32_t horizontalTextOffset;
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        ofPushMatrix(); // Save the current drawing context
        if (_firstRender) std::cout << "pushM\n";
        // set the relative position from bounds
        ofTranslate(bounds.x, bounds.y);
        
        // NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        // Textbox-specific drawing code here
        if (_firstRender) {
            std::cout << "NfTextInputField: " << _name << std::endl;
            _firstRender=false;
        }
        // For example, draw the textbox area
        ofSetColor(backgroundColor.get());
        ofDrawRectangle(bounds); // Assuming bounds is accessible
        
        // Draw the text inside the textbox
        ofSetColor(textColor.get());
        
        NFValue* valueRawPtr = this->getValue();
        if (valueRawPtr != nullptr) {
            std::string valueAsString = valueRawPtr->toString();
            // calculate text position 
            horizontalTextOffset = _config.paddingLeft;
            verticalTextOffset = BITMAP_FONT_SIZE + _config.paddingTop;
            ofDrawBitmapString(valueAsString, bounds.x + horizontalTextOffset, bounds.y + verticalTextOffset); // Placeholder for text drawing
        } else {
            std::cout << "NfTextInputField: " << _name << ":no value available." << std::endl;
        }
        ofPopMatrix(); // Restore the drawing context
        if (_firstRender) std::cout << "popM\n";
    }
    
    // Additional methods specific to textbox, like text input handling
};

}

#endif /* NfTextInputField_hpp */
