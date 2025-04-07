//
//  NfSelection.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#include "NfSelection.hpp"

namespace nfUI {

void NfSelection::draw() {
    ofPushMatrix(); // Save the current drawing context
    NfBoxxer::draw(); // Call base class draw for common drawing code if needed
    
    // Selection-specific drawing code here
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "NfSelection: " << _name << std::endl;
        }
        // Initialize selection value
        selectionValue = dynamic_cast<SelectionNFValue*>(this->getValue());
        if (selectionValue == nullptr) {
            std::cout << "NfSelection: " << _name << ": no selection value available." << std::endl;
        }
        _firstRender = false;
    }
    
    float textfieldWidth = bounds.width;
    // Draw the label text
    ofSetColor(textColor.get());
    if (_config.showLabel) {
        ofDrawBitmapString(_name, 0, BITMAP_FONT_SIZE + _config.paddingTop);
        textfieldWidth /= 2;
        boundsMouse.width /= 2;
    }
    
    // draw the background text panel
    if (_config.showLabel) {
        ofTranslate(textfieldWidth, 0);
        translateBounds(boundsMouse, textfieldWidth, 0, _name);
    }

    ofColor bgBackgroundColor = backgroundColor.get();
    ofColor bgFocusBackgroundColor = focusBackgroundColor.get();
    
    // when the element has the focus set it to full alpha
    if (isFocused.get()) {
        bgBackgroundColor.a = 255;
        bgFocusBackgroundColor.a = 255;
    }
    
    // draw background
    ofSetColor(bgBackgroundColor);
    ofDrawRectangle(0, 0, textfieldWidth, bounds.height);
    
    // draw current selection
    if (selectionValue != nullptr) {
        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(textColor.get());
        }
        ofDrawBitmapString(selectionValue->getSelectedName(), _config.paddingLeft, BITMAP_FONT_SIZE + _config.paddingTop);
    }
    
    // draw dropdown if open
    if (_isDropdownOpen) {
        drawDropdown();
    }
    
    ofPopMatrix(); // Restore the drawing context
}

void NfSelection::drawDropdown() {
    if (selectionValue == nullptr) return;
    
    const auto& names = selectionValue->getNamesList();
    _dropdownHeight = names.size() * _itemHeight;
    
    // draw dropdown background
    ofSetColor(backgroundColor.get());
    ofDrawRectangle(0, bounds.height, bounds.width, _dropdownHeight);
    
    // draw items
    for (size_t i = 0; i < names.size(); ++i) {
        if (i == _hoveredItem) {
            ofSetColor(focusBackgroundColor.get());
            ofDrawRectangle(0, bounds.height + i * _itemHeight, bounds.width, _itemHeight);
        }
        
        if (i == selectionValue->getIndex()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(textColor.get());
        }
        ofDrawBitmapString(names[i], _config.paddingLeft, bounds.height + (i + 1) * _itemHeight - 4);
    }
}

void NfSelection::updateDropdownHeight() {
    if (selectionValue != nullptr) {
        _dropdownHeight = selectionValue->getNamesList().size() * _itemHeight;
    }
}

bool NfSelection::isPointInDropdown(const ofPoint& point) const {
    if (!_isDropdownOpen) return false;
    return point.y >= bounds.height && point.y <= bounds.height + _dropdownHeight;
}

int NfSelection::getItemIndexAtPoint(const ofPoint& point) const {
    if (!isPointInDropdown(point)) return -1;
    return static_cast<int>((point.y - bounds.height) / _itemHeight);
}

void NfSelection::setSelectionValue(SelectionNFValue* value) {
    selectionValue = value;
    updateDropdownHeight();
}

bool NfSelection::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = true;
                _isDropdownOpen = !_isDropdownOpen;
                return true;
            } else if (_isDropdownOpen && isPointInDropdown(localPoint)) {
                int itemIndex = getItemIndexAtPoint(localPoint);
                if (itemIndex >= 0 && selectionValue != nullptr) {
                    selectionValue->setIndex(itemIndex);
                    _isDropdownOpen = false;
                    UIEventArgs eventArgs;
                    ofNotifyEvent(selectionChanged, eventArgs, this);
                }
                return true;
            } else if (_isDropdownOpen) {
                _isDropdownOpen = false;
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_MOVED:
            if (boundsMouse.inside(localPoint) || (_isDropdownOpen && isPointInDropdown(localPoint))) {
                parameters.getBool("IsFocused") = true;
                if (_isDropdownOpen) {
                    _hoveredItem = getItemIndexAtPoint(localPoint);
                }
                setHandCursor();
                return true;
            } else {
                if (parameters.getBool("IsFocused") == true) {
                    parameters.getBool("IsFocused") = false;
                    _hoveredItem = -1;
                }
            }
            return false;
            
        case AppEventType::MOUSE_EXITED:
            if (!boundsMouse.inside(localPoint) && !(_isDropdownOpen && isPointInDropdown(localPoint))) {
                parameters.getBool("IsFocused") = false;
                _hoveredItem = -1;
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI 