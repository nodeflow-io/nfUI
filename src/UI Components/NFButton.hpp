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
    uint32_t verticalTextOffset; // font size dependant
    uint32_t horizontalTextOffset;
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        ofPushMatrix();
        NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        if (_firstRender) {
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
        drawChildren(_config.paddingLeft, _config.paddingTop);
        
        ofPopMatrix(); // Restore the drawing context
    }
};

}

#endif /* NfButton_hpp */
