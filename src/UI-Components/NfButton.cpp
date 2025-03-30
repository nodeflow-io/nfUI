//
//  NFButton.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NfButton.hpp"

namespace nfUI {

void NfButton::draw() {
    ofPushMatrix();
    NfBoxxer::draw(); // Call base class draw for common drawing code if needed
    
    if (_firstRender) {
        ofRegisterMouseEvents(this);
        if (_config.isDebug) {
            std::cout << "NfButton: " << _name << std::endl;
        }
        _firstRender = false;
    }

    if (isFocused.get()) {
        ofSetColor(focusBackgroundColor.get());
    } else {
        ofSetColor(backgroundColor.get());
    }
    
    // get Dimensions children requires
    // this->getDimensions(_config.width, _config.height);
    
    // draw own Background
    ofDrawRectangle(0, 0, bounds.width, bounds.height);
    
    if (isFocused.get()) {
        ofSetColor(focusColor.get());
    } else {
        ofSetColor(textColor.get());
    }
    NFValue* valueRawPtr = this->getValue();
    if (valueRawPtr != nullptr) {
        std::string valueAsString = valueRawPtr->toString();
        // calculate text position
        horizontalTextOffset = _config.paddingLeft;
        verticalTextOffset = BITMAP_FONT_SIZE + _config.paddingTop;
        ofDrawBitmapString(valueAsString, horizontalTextOffset, verticalTextOffset);
    } else {
        std::cout << "NfButton: " << _name << ":no value available." << std::endl;
    }
    
    // call drawChildren with the current paddings
    // drawChildren(_config.paddingLeft, _config.paddingTop);
    
    ofPopMatrix(); // Restore the drawing context
}

void NfButton::mouseDragged(ofMouseEventArgs& args) {
}

void NfButton::mousePressed(ofMouseEventArgs& args) {
    // Handle mouse pressed event for the button, if needed
    mouseDownInRect = boundsMouse.inside(args.x, args.y);
    if(mouseDownInRect) {
        parameters.getBool("IsFocused") = true; // Set to true
    }
    // std::cout << "mousePressed" << _name << ": " << boundsMouse.x << std::endl;
}

void NfButton::mouseMoved(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        parameters.getBool("IsFocused") = true;
        // ofSetCursor(OF_CURSOR_HAND);
    } else {
        parameters.getBool("IsFocused") = false;
        // ofSetCursor(OF_CURSOR_ARROW);
    }
}

void NfButton::mouseScrolled(ofMouseEventArgs& args) {
}

void NfButton::mouseEntered(ofMouseEventArgs& args) {
}

void NfButton::mouseExited(ofMouseEventArgs& args) {
}

void NfButton::mouseReleased(ofMouseEventArgs& args) {
    // Handle mouse released event for the button, if needed
    mouseDownInRect = boundsMouse.inside(args.x, args.y);
    if (mouseDownInRect) {
        UIEventArgs eventArgs;
        ofNotifyEvent(clicked, eventArgs, this);
        parameters.getBool("IsFocused") = false; // Set to true
    }
}

} // namespace nfUI
