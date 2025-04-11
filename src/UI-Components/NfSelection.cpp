//
//  NfSelection.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#include "NfSelection.hpp"

namespace nfUI {

void NfSelection::draw() {
    // First render initialization
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "NfSelection: " << _name << std::endl;
        }
        // Try to initialize the selection value if not already done
        if (selectionValue == nullptr) {
            NFValue* baseValue = this->getValue();
            if (baseValue) {
                selectionValue = dynamic_cast<SelectionNFValue*>(baseValue);
                if (selectionValue == nullptr) {
                    ofLogError("NfSelection") << _name << ": Cannot cast value to SelectionNFValue. Check value type.";
                }
            } else {
                ofLogError("NfSelection") << _name << ": No value available.";
            }
        }
        
        _firstRender = false;
    }
    
    // Call base class draw for setup of transformations
    NfBoxxer::draw();
    
    // Draw the base selection element
    drawBaseElement();
    
    // NOTE: We don't draw the dropdown here anymore
    // It will be drawn during the floating elements pass in NfBoxxer::drawChildren
    
    // Call children draw method with appropriate padding
    drawChildren(_config.paddingLeft, _config.paddingTop);
    
    // End the drawing transform stack (started in NfBoxxer::draw())
    ofPopMatrix();
}

void NfSelection::drawBaseElement() {
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "NfSelection: " << _name << std::endl;
        }
        // This initialization has moved to draw() method
        _firstRender = false;
    }
    
    float textfieldWidth = bounds.width;
    // Draw the label text
    ofSetColor(textColor.get());
    if (_config.showLabel) {
        ofDrawBitmapString(_name, 0, BITMAP_FONT_SIZE + _config.paddingTop);
        textfieldWidth /= 2;
        boundsMouse.width = textfieldWidth;
        // draw the background text pannel
        ofTranslate(textfieldWidth, 0);
        // Calculate relative boundsMouse coordinates by subtracting boundsMouse from parent position
        if (auto parentPtr = parent.lock()) {
            boundsMouse.x = parentPtr->boundsMouse.x + parentPtr->_config.paddingLeft 
            + _config.paddingLeft + textfieldWidth;
        }
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
        // Draw the actual selected name
        ofDrawBitmapString(selectionValue->getSelectedName(), _config.paddingLeft, BITMAP_FONT_SIZE + _config.paddingTop);
    } else {
        // Draw placeholder if no selection value
        ofSetColor(textColor.get());
        ofDrawBitmapString("No selection", _config.paddingLeft, BITMAP_FONT_SIZE + _config.paddingTop);
    }
}

void NfSelection::drawDropdown() {
    if (selectionValue == nullptr) return;
    
    // Determine the dropdown width - half width when showing label
    float dropdownWidth = _config.showLabel ? (bounds.width / 2) : bounds.width;
    
    // Use the dropdown offset for positioning
    float dropdownOffset = getDropdownOffset();
    
    // Safely get names vector with null/empty checks
    const std::vector<std::string>& names = selectionValue->getNamesList();
    if (names.empty()) {
        _dropdownHeight = 0;
        return; // Exit early if no names to display
    }
    
    _dropdownHeight = names.size() * _itemHeight;
    
    // Draw dropdown background - positioned relative to selection element
    ofSetColor(backgroundColor.get());
    ofDrawRectangle(0, bounds.height + dropdownOffset, dropdownWidth, _dropdownHeight);
    
    // Draw items
    for (size_t i = 0; i < names.size(); ++i) {
        if (i == _hoveredItem) {
            ofSetColor(focusBackgroundColor.get());
            ofDrawRectangle(0, bounds.height + dropdownOffset + i * _itemHeight, dropdownWidth, _itemHeight);
        }
        
        if (i == selectionValue->getIndex()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(textColor.get());
        }
        ofDrawBitmapString(names[i], _config.paddingLeft, 
                          bounds.height + dropdownOffset + (i + 1) * _itemHeight - 4);
    }
}

void NfSelection::updateDropdownHeight() {
    if (selectionValue == nullptr) return;
    
    // Get names list safely
    const auto& names = selectionValue->getNamesList();
    // Calculate dropdown height only if we have items
    _dropdownHeight = names.empty() ? 0 : names.size() * _itemHeight;
}

bool NfSelection::isPointInDropdown(const ofPoint& point) const {
    if (!_isDropdownOpen || selectionValue == nullptr) return false;
    
    // If names list is empty, there's no dropdown to check
    const auto& names = selectionValue->getNamesList();
    if (names.empty()) return false;
    
    // Calculate dropdown width based on whether label is shown
    float dropdownWidth = _config.showLabel ? (bounds.width / 2) : bounds.width;
    
    // Use the dropdown offset for hit testing
    float dropdownOffset = getDropdownOffset();
    
    // Convert global coordinates to local space relative to dropdown
    // For global coordinates, we need to check against boundsMouse (global bounds)
    float dropdownX = boundsMouse.x;
    float dropdownY = boundsMouse.y + bounds.height + dropdownOffset;
    
    // Check if the point is within the dropdown's bounds using global coordinates
    return (point.x >= dropdownX && 
            point.x <= dropdownX + dropdownWidth && 
            point.y >= dropdownY && 
            point.y <= dropdownY + _dropdownHeight);
}

int NfSelection::getItemIndexAtPoint(const ofPoint& point) const {
    if (!isPointInDropdown(point) || selectionValue == nullptr) return -1;
    
    // Use the dropdown offset for calculation
    float dropdownOffset = getDropdownOffset();
    float dropdownY = boundsMouse.y + bounds.height + dropdownOffset;
    
    // Calculate index based on position in global coordinates
    int calculatedIndex = static_cast<int>((point.y - dropdownY) / _itemHeight);
    
    // Verify index is within bounds of our names list
    const auto& names = selectionValue->getNamesList();
    if (calculatedIndex < 0 || calculatedIndex >= names.size()) {
        return -1; // Out of bounds
    }
    
    return calculatedIndex;
}

void NfSelection::setSelectionValue(SelectionNFValue* value) {
    selectionValue = value;
    if (selectionValue == nullptr) {
        ofLogWarning("NfSelection") << _name << ": Setting null selection value.";
        _dropdownHeight = 0;
        return;
    }
    updateDropdownHeight();
}

bool NfSelection::handleFloatingElementEvent(AppEventType type, const ofPoint& point, int button) {
    if (!_isDropdownOpen) return false;
    
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            // Check if the press is in the selection box itself (not the dropdown)
            if (boundsMouse.inside(point)) {
                _mousePressedInSelection = true;
                _dropdownStateChanged = false;  // Reset state change tracking
                return true;
            }
            
            if (isPointInDropdown(point)) {
                // Store the item where the mouse was pressed
                _pressedDropdownItem = getItemIndexAtPoint(point);
                _mousePressedInDropdown = true;
                return true;
            }
            break;
            
        case AppEventType::MOUSE_RELEASED:
            // If pressed and released in the selection box, close the dropdown
            if (_mousePressedInSelection && boundsMouse.inside(point)) {
                // Get current time to check if dropdown was recently closed
                uint64_t currentTime = ofGetElapsedTimeMillis();
                
                // If the dropdown was closed within the last 300ms, don't do anything
                if ((currentTime - _lastDropdownCloseTime) < 300) {
                    _mousePressedInSelection = false;
                    return true;
                }
                
                // Only close if we haven't already changed the state
                if (!_dropdownStateChanged) {
                    _isDropdownOpen = false;
                    _lastDropdownCloseTime = ofGetElapsedTimeMillis(); // Update timestamp
                    _dropdownStateChanged = true;
                }
                _mousePressedInSelection = false;
                return true;
            }
            
            if (_mousePressedInDropdown && isPointInDropdown(point)) {
                // Check if released on the same item as pressed
                int releasedItemIndex = getItemIndexAtPoint(point);
                
                if (releasedItemIndex == _pressedDropdownItem && releasedItemIndex >= 0 && selectionValue != nullptr) {
                    selectionValue->setIndex(releasedItemIndex);
                    _isDropdownOpen = false;
                    _lastDropdownCloseTime = ofGetElapsedTimeMillis(); // Update timestamp
                    _dropdownStateChanged = true;
                    UIEventArgs eventArgs;
                    ofNotifyEvent(selectionChanged, eventArgs, this);
                }
                
                _mousePressedInDropdown = false;
                _pressedDropdownItem = -1;
                return true;
            }
            break;
            
        case AppEventType::MOUSE_MOVED:
            if (isPointInDropdown(point)) {
                _hoveredItem = getItemIndexAtPoint(point);
                setHandCursor();
                return true;
            }
            break;
            
        default:
            break;
    }
    
    return false;
}

void NfSelection::update() {
    // Update animations or transitions related to the dropdown
    
    // Example: Handle auto-closing of dropdowns that have been open too long
    if (_isDropdownOpen) {
        uint64_t currentTime = ofGetElapsedTimeMillis();
        uint64_t openDuration = currentTime - _lastDropdownCloseTime;
        
        // Auto-close dropdown if it's been open for more than 10 seconds with no interaction
        // This helps prevent forgotten open dropdowns
        if (openDuration > 10000 && _hoveredItem == -1) {
            _isDropdownOpen = false;
            _lastDropdownCloseTime = currentTime;
            _dropdownStateChanged = true;
        }
    }
    
    // Update any hover animations or transitions here
    
    // Call parent's update method to handle children
    NfBoxxer::update();
}

bool NfSelection::handleRoutedMouseEvent(AppEventType type, const ofPoint& globalPoint, int button) {
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(globalPoint)) {
                parameters.getBool("IsFocused") = true;
                _mousePressedInSelection = true;  // Track mouse press in selection area
                _dropdownStateChanged = false;    // Reset state change tracking for this click cycle
                return true;
            } else if (_isDropdownOpen && isPointInDropdown(globalPoint)) {
                // Store the dropdown item where mouse was pressed
                _pressedDropdownItem = getItemIndexAtPoint(globalPoint);
                _mousePressedInDropdown = true;
                return true;
            } else if (_isDropdownOpen) {
                // Close dropdown if clicked outside
                _isDropdownOpen = false;
                _lastDropdownCloseTime = ofGetElapsedTimeMillis(); // Update timestamp
                _dropdownStateChanged = true;     // Mark that we changed the state during this click
                return true;
            }
            return false;
            
        case AppEventType::MOUSE_RELEASED:
            if (_mousePressedInSelection && boundsMouse.inside(globalPoint)) {
                _mousePressedInSelection = false;
                
                // Get current time to check if dropdown was recently closed
                uint64_t currentTime = ofGetElapsedTimeMillis();
                
                // If the dropdown was closed within the last 100ms, don't reopen it
                if ((currentTime - _lastDropdownCloseTime) < 100) {
                    // Dropdown was just closed, don't toggle
                    _dropdownStateChanged = false;
                    return true;
                }
                
                // Only toggle the dropdown if we haven't already changed state during this click cycle
                if (!_dropdownStateChanged) {
                    // Toggle from current state
                    _isDropdownOpen = !_isDropdownOpen;
                    
                    // If we closed the dropdown, update the timestamp
                    if (!_isDropdownOpen) {
                        _lastDropdownCloseTime = ofGetElapsedTimeMillis();
                    }
                }
                
                // Reset state change tracking after handling the release
                _dropdownStateChanged = false;
                return true;
            } else if (_mousePressedInDropdown && _isDropdownOpen && isPointInDropdown(globalPoint)) {
                // Mouse was pressed and released in dropdown
                int releasedItemIndex = getItemIndexAtPoint(globalPoint);
                
                // Only trigger if released on the same item that was pressed
                if (releasedItemIndex == _pressedDropdownItem && releasedItemIndex >= 0 && selectionValue != nullptr) {
                    selectionValue->setIndex(releasedItemIndex);
                    _isDropdownOpen = false;
                    _lastDropdownCloseTime = ofGetElapsedTimeMillis(); // Update timestamp
                    _dropdownStateChanged = true;
                    UIEventArgs eventArgs;
                    ofNotifyEvent(selectionChanged, eventArgs, this);
                }
                
                _mousePressedInDropdown = false;
                _pressedDropdownItem = -1;
                return true;
            }
            
            // Reset all mouse press states on release
            _mousePressedInSelection = false;
            _mousePressedInDropdown = false;
            _pressedDropdownItem = -1;
            _dropdownStateChanged = false;        // Reset state change tracking
            return false;
            
        case AppEventType::MOUSE_MOVED:
            if (boundsMouse.inside(globalPoint) || (_isDropdownOpen && isPointInDropdown(globalPoint))) {
                parameters.getBool("IsFocused") = true;
                if (_isDropdownOpen) {
                    _hoveredItem = getItemIndexAtPoint(globalPoint);
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
            if (!boundsMouse.inside(globalPoint) && !(_isDropdownOpen && isPointInDropdown(globalPoint))) {
                parameters.getBool("IsFocused") = false;
                _hoveredItem = -1;
                _dropdownStateChanged = false;     // Reset state change tracking
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI 
