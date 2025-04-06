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

bool NfButton::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                mouseDownInRect = true;
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_RELEASED:
            if (mouseDownInRect && boundsMouse.inside(localPoint)) {
                UIEventArgs eventArgs;
                ofNotifyEvent(clicked, eventArgs, this);
                parameters.getBool("IsFocused") = false;
            }
            mouseDownInRect = false;
            return true;
            
        case AppEventType::MOUSE_MOVED:
            // Always check whether we're inside or outside on MOUSE_MOVED
            // This ensures proper focus state even with hierarchical event routing
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                return true;
            } else {
                // If we were previously focused and mouse has moved out, update state
                if (parameters.getBool("IsFocused") == true) {
                    parameters.getBool("IsFocused") = false;
                    // No need to return true here - let parent handle events outside our bounds
                }
            }
            return false;
            
        case AppEventType::MOUSE_EXITED:
            if (!boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = false;
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI
