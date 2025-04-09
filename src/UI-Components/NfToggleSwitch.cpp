//
//  NfToggleSwitch.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#include "NfToggleSwitch.hpp"

namespace nfUI {

void NfToggleSwitch::draw() {
    // First render initialization
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "NfToggleSwitch: " << _name << std::endl;
        }
        // Init text as string from value
        valueRawPtr = this->getValue();
        if (valueRawPtr != nullptr) {
            std::string valueAsString = valueRawPtr->toString();
            this->text = valueAsString;
        } else {
            this->text = "";
            std::cout << "NfToggleSwitch: " << _name << ":no value available." << std::endl;
        }

        // setup

        _firstRender = false;
    }
    
    // Call base class draw for setup of transformations
    NfBoxxer::draw();
    
    float textfieldWith = bounds.width;
    // Draw the label text
    ofSetColor(textColor.get());
    if (_config.showLabel) {
        ofDrawBitmapString(_name, 0, BITMAP_FONT_SIZE + _config.paddingTop);
        textfieldWith /= 2;
        boundsMouse.width = textfieldWith;
        // draw the background text pannel
        ofTranslate(textfieldWith, 0);
        if (auto parentPtr = parent.lock()) {
            boundsMouse.x = parentPtr->boundsMouse.x + parentPtr->_config.paddingLeft 
            + _config.paddingLeft + textfieldWith;
        }
    }

    NFValue* valueRawPtr = this->getValue();
    bool valueAsBool;
    std::string valueAsString;
    if (valueRawPtr != nullptr) {
        valueAsBool = valueRawPtr->toBool();
        valueAsString = valueRawPtr->toString();
        this->text = valueAsString;
    } else {
        this->text = "";
        std::cout << "NfToggleSwitch: " << _name << ":no value available." << std::endl;
    }
    ofColor bgBackgroundColor = backgroundColor.get();
    ofColor bgFocusBackgroundColor = focusBackgroundColor.get();
    
    // when the element has the focus set it to full aplha
    if (isFocused.get()) {
        bgBackgroundColor.a = 255;
        bgFocusBackgroundColor.a = 255;
    };
    
    if (valueAsBool) {
        ofSetColor(bgFocusBackgroundColor);
    } else {
        ofSetColor(bgBackgroundColor);
    }
    
    // draw background
    ofDrawRectangle(0,0, textfieldWith, bounds.height);
    
    if (isFocused.get()) {
        ofSetColor(focusColor.get());
    } else {
        ofSetColor(textColor.get());
    }
    
    // draw value
    ofDrawBitmapString(valueAsString, _config.paddingLeft, BITMAP_FONT_SIZE + _config.paddingTop);

    // Call children draw method with appropriate padding
    drawChildren(_config.paddingLeft, _config.paddingTop);
    
    // End the drawing transform stack (started in NfBoxxer::draw())
    ofPopMatrix();
}

bool NfToggleSwitch::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                _mousePressedInToggle = true;  // Track that mouse was pressed in toggle
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_RELEASED:
            // Only trigger the action if the mouse was both pressed and released inside the toggle
            if (_mousePressedInToggle && boundsMouse.inside(localPoint)) {
                // Toggle the value
                UIEventArgs eventArgs;
                ofNotifyEvent(clicked, eventArgs, this);
            }
            
            // Reset the pressed state
            _mousePressedInToggle = false;
            
            // Return true if we're inside the bounds to consume the event
            return boundsMouse.inside(localPoint);
            
        case AppEventType::MOUSE_MOVED:
            // Always check whether we're inside or outside on MOUSE_MOVED
            // This ensures proper focus state even with hierarchical event routing
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                setHandCursor();
                return true;
            } else {
                // If we were previously focused and mouse has moved out, update state
                if (parameters.getBool("IsFocused") == true) {
                    parameters.getBool("IsFocused") = false;
                    // No need to return true here - let parent handle events outside our bounds
                }
                
                // Also clear the pressed state if mouse moves out
                _mousePressedInToggle = false;
            }
            return false;
            
        case AppEventType::MOUSE_EXITED:
            if (!boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = false;
                _mousePressedInToggle = false;  // Clear pressed state when exiting
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI