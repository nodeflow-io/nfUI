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
    
protected:
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset; // font size dependant
    uint32_t horizontalTextOffset;
    bool mouseDownInRect;
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // Event declaration
    ofEvent<UIEventArgs> clicked;
    
    void draw() override {
        ofPushMatrix();
        NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        if (_firstRender) {
            ofRegisterMouseEvents(this);
            if (_config.isDebug) {
                std::cout << "NfButton: " << _name << std::endl;
            }
            _firstRender=false;
        }

        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }

        
        // get Dimensions children requires
        // this->getDimensions(_config.width, _config.height);
        
        // draw own Background
        ofDrawRectangle(0, 0, bounds.width, bounds.height);
        
        ofSetColor(textColor.get());
        
        NFValue* valueRawPtr = this->getValue();
        if (valueRawPtr != nullptr) {
            std::string valueAsString = valueRawPtr->toString();
            // calculate text position
            horizontalTextOffset = _config.paddingLeft;
            verticalTextOffset = BITMAP_FONT_SIZE + _config.paddingTop;
            ofDrawBitmapString(valueAsString, horizontalTextOffset, verticalTextOffset); // Placeholder for text drawing
        } else {
            std::cout << "NfButton: " << _name << ":no value available." << std::endl;
        }
        
        // call drawChildren with the current paddings
        // drawChildren(_config.paddingLeft, _config.paddingTop);
        
        ofPopMatrix(); // Restore the drawing context
    }
    
    void mouseDragged(ofMouseEventArgs& args) {
    }
    
    void mousePressed(ofMouseEventArgs& args) {
        // Handle mouse pressed event for the button, if needed
        mouseDownInRect = boundsMouse.inside(args.x, args.y);
        if(mouseDownInRect) {
            parameters.getBool("IsFocused") = true; // Set to true
        }
    }
    
    void mouseMoved(ofMouseEventArgs& args) {
    }
    
    void mouseScrolled(ofMouseEventArgs& args) {
    }
    
    void mouseEntered(ofMouseEventArgs& args) {
    }
    
    void mouseExited(ofMouseEventArgs& args) {
    }

    void mouseReleased(ofMouseEventArgs& args) {
        // Handle mouse released event for the button, if needed
        mouseDownInRect = boundsMouse.inside(args.x, args.y);
        if (mouseDownInRect) {
            UIEventArgs eventArgs;
            ofNotifyEvent(clicked, eventArgs, this);
            parameters.getBool("IsFocused") = false; // Set to true
        }
    }
};

}

#endif /* NfButton_hpp */
