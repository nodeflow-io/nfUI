//
//  NfLabel.hpp
//  nodeflowUI
//
//  Created by Matthias Srohmaier on 23.02.24.
//

#ifndef NfLabel_hpp
#define NfLabel_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfLabel : public NfBoxxer {
    
private:
    bool _firstRender = true;   // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset; 
    uint32_t horizontalTextOffset;
    bool _isDragging = false;   // Flag to track if the panel is being dragged
    ofPoint _dragStartPos;      // Starting point of a drag
    ofPoint _panelStartPos;     // Offset from the initial drag point
    
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
                std::cout << "NfLabel: " << _name << std::endl;
            }
            _firstRender=false;
        }

        if (isFocused.get()) {
            ofSetColor(focusBackgroundColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }
        
        // draw own Background
        ofDrawRectangle(0, 0, bounds.width, bounds.height);
        
        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(textColor.get());
        }
        
        ofSetColor(textColor.get());
        
        NFValue* valueRawPtr = this->getValue();
        if (valueRawPtr != nullptr) {
            std::string valueAsString = valueRawPtr->toString();
            // calculate text position
            horizontalTextOffset = _config.paddingLeft;
            verticalTextOffset = BITMAP_FONT_SIZE + _config.paddingTop;
            ofDrawBitmapString(valueAsString, horizontalTextOffset, verticalTextOffset); // Placeholder for text drawing
        } else {
            std::cout << "NfLabel: " << _name << ":no value available." << std::endl;
        }
        
        // call drawChildren with the current paddings
        // drawChildren(_config.paddingLeft, _config.paddingTop);
        
        ofPopMatrix(); // Restore the drawing context
    }
    
    // mouse event handling -------------------
    
    void mouseDragged(ofMouseEventArgs& args) {
        if(_isDragging) {
            // Calculate the new position based on the drag
            ofPoint newPos = _panelStartPos + (ofPoint(args.x, args.y) - _dragStartPos);
            setPosition(newPos);
        }
    }
    
    void mousePressed(ofMouseEventArgs& args) {
        // Check if the click is inside the panel's bounds
        if(boundsMouse.inside(args.x, args.y)) {
            _isDragging = true;
            _dragStartPos.set(args.x, args.y);
            this->getPosition(_panelStartPos);
        }
    }
    
    void mouseMoved(ofMouseEventArgs& args) {
        if(boundsMouse.inside(args.x, args.y)) {
            parameters.getBool("IsFocused") = true;
            // ofSetCursor(OF_CURSOR_HAND);
        } else {
            parameters.getBool("IsFocused") = false;
            // ofSetCursor(OF_CURSOR_ARROW);
        }
    }
    
    void mouseScrolled(ofMouseEventArgs& args) {
    }
    
    void mouseEntered(ofMouseEventArgs& args) {

    }
    
    void mouseExited(ofMouseEventArgs& args) {
 
    }

    void mouseReleased(ofMouseEventArgs& args) {
        _isDragging = false;
    }
};

}

#endif /* NfLabel_hpp */
