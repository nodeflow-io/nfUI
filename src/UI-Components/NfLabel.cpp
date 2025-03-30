//
//  NfLabel.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#include "NfLabel.hpp"

namespace nfUI {

void NfLabel::draw() {
    ofPushMatrix();
    NfBoxxer::draw(); // Call base class draw for common drawing code if needed
    
    if (_firstRender) {
        ofRegisterMouseEvents(this);
        if (_config.isDebug) {
            std::cout << "NfLabel: " << _name << std::endl;
        }
        _firstRender = false;
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

void NfLabel::mouseDragged(ofMouseEventArgs& args) {
    if(_isDragging) {
        // Calculate the new position based on the drag
        ofPoint newPos = _panelStartPos + (ofPoint(args.x, args.y) - _dragStartPos);
        setPosition(newPos);
    }
}

void NfLabel::mousePressed(ofMouseEventArgs& args) {
    // Check if the click is inside the panel's bounds
    if(boundsMouse.inside(args.x, args.y)) {
        _isDragging = true;
        _dragStartPos.set(args.x, args.y);
        this->getPosition(_panelStartPos);
    }
}

void NfLabel::mouseMoved(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        parameters.getBool("IsFocused") = true;
        // ofSetCursor(OF_CURSOR_HAND);
    } else {
        parameters.getBool("IsFocused") = false;
        // ofSetCursor(OF_CURSOR_ARROW);
    }
}

void NfLabel::mouseScrolled(ofMouseEventArgs& args) {
}

void NfLabel::mouseEntered(ofMouseEventArgs& args) {
}

void NfLabel::mouseExited(ofMouseEventArgs& args) {
}

void NfLabel::mouseReleased(ofMouseEventArgs& args) {
    _isDragging = false;
}

} // namespace nfUI
