//
//  NFButton.hpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 21.02.24.
//

#ifndef NFButton_hpp
#define NFButton_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfButton : public NfBoxxer {
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        // Button-specific drawing code here
        std::cout << "Drawing Button: " << _name << std::endl;
        // For example, draw a rectangle with a different color when focused
        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }
        ofDrawRectangle(bounds); // Assuming bounds is accessible
        // Draw the label/text of the button
    }
};

}

#endif /* NFButton_hpp */
