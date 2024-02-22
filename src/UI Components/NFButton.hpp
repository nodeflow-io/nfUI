//
//  NfButton.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaie on 21.02.24.
//

#ifndef NfButton_hpp
#define NfButton_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfButton : public NfBoxxer {
    
private:
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        // Button-specific drawing code here
        if (_firstRender) {
            std::cout << "NfButton: " << _name << std::endl;
            _firstRender=false;
        }
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

#endif /* NfButton_hpp */
