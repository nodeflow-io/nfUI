//
//  NfToggleSwitch.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#include "NfToggleSwitch.hpp"

namespace nfUI {

void NfToggleSwitch::draw() {
    ofPushMatrix(); // Save the current drawing context
    NfBoxxer::draw(); // Call base class draw for common drawing code if needed
    
    // Textbox-specific drawing code here
    if (_firstRender) {
        ofRegisterMouseEvents(this);
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
        _firstRender = false;
    }
    
    float textfieldWith = bounds.width;
    // Draw the label text
    ofSetColor(textColor.get());
    if (_config.showLabel) {
        ofDrawBitmapString(_name, 0, BITMAP_FONT_SIZE + _config.paddingTop);
        textfieldWith /= 2;
        boundsMouse.width /= 2;
    }
    
    // draw the background text pannel
    if (_config.showLabel) {
        ofTranslate(textfieldWith, 0);
        translateBounds(boundsMouse, textfieldWith, 0, _name);
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

    ofPopMatrix(); // Restore the drawing context
}

void NfToggleSwitch::mouseDragged(ofMouseEventArgs& args) {
}

void NfToggleSwitch::mousePressed(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        parameters.getBool("IsFocused") = true;
        // ofSetCursor(OF_CURSOR_HAND);
        UIEventArgs eventArgs;
        ofNotifyEvent(clicked, eventArgs, this);
    }
}

void NfToggleSwitch::mouseMoved(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        parameters.getBool("IsFocused") = true;
        // ofSetCursor(OF_CURSOR_HAND);
    } else {
        parameters.getBool("IsFocused") = false;
        // ofSetCursor(OF_CURSOR_ARROW);
    }
}

void NfToggleSwitch::mouseScrolled(ofMouseEventArgs& args) {
}

void NfToggleSwitch::mouseEntered(ofMouseEventArgs& args) {
}

void NfToggleSwitch::mouseExited(ofMouseEventArgs& args) {
}

void NfToggleSwitch::mouseReleased(ofMouseEventArgs& args) {
}

} // namespace nfUI