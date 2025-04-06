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
    
    // draw own Background - use bounds which is more accurate
    // Subtract borderSize to account for parent border rendering
    // This prevents the 1px wider appearance
    ofDrawRectangle(0, 0, bounds.width - borderSize, bounds.height - borderSize);
    
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
    
    ofPopMatrix(); // Restore the drawing context
}

bool NfLabel::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    return false;
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                _isDragging = true;
                _dragStartPos.set(localPoint.x, localPoint.y);
                getPosition(_panelStartPos);
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_DRAGGED:
            if (_isDragging) {
                ofPoint newPos = _panelStartPos + (ofPoint(localPoint.x, localPoint.y) - _dragStartPos);
                setPosition(newPos);
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_RELEASED:
            _isDragging = false;
            return true;
            
        case AppEventType::MOUSE_MOVED:
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                return true;
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

