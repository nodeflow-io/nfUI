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
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        // Textbox-specific drawing code here
        std::cout << "Drawing Textbox: " << _name << std::endl;
        // For example, draw the textbox area
        ofSetColor(backgroundColor.get());
        ofDrawRectangle(bounds); // Assuming bounds is accessible
        
        // Draw the text inside the textbox
        ofSetColor(textColor.get());
        // You might need a method to draw text in openFrameworks, like ofDrawBitmapString
        ofDrawBitmapString(text, bounds.x, bounds.y); // Placeholder for text drawing
    }
    
    // Additional methods specific to textbox, like text input handling
};

}

#endif /* NfTextInputField_hpp */
