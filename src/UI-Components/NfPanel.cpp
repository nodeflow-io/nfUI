//
//  NfPanel.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#include "NfPanel.hpp"

namespace nfUI {

void NfPanel::draw() {
    // First render initialization
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "NfPanel: " << _name << std::endl;
        }
        _firstRender = false;
        markDimensionsDirty();  // Ensure dimensions are calculated on first render
    }
    
    // Call base class to handle bounds calculation and transformations
    NfBoxxer::draw();
    
    // Draw the panel background
    if (nodeIsFocused || isFocused.get()) {
        ofSetColor(focusBackgroundColor.get());
    } else {
        ofSetColor(backgroundColor.get());
    }
    
    // Get dimensions children requires
    float width, height;
    this->getDimensions(width, height);
    _config.width = width;
    _config.height = height;
    
    // Draw the panel background - using (0,0) because NfBoxxer::draw() already set up the transform
    ofDrawRectangle(0, 0, _config.width, _config.height);
    
    // Draw all children
    drawChildren(_config.paddingLeft, _config.paddingTop);
    
    // End the drawing transform stack (started in NfBoxxer::draw())
    ofPopMatrix();
}

bool NfPanel::routeMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    // For MOUSE_MOVED, we need to propagate focus changes even if child handles event
    bool sendToAll = (type == AppEventType::MOUSE_MOVED);
    bool consumed = false;
    
    // Process children in reverse order (topmost/last drawn first)
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        
        // Check if the point is inside the child's bounds
        bool isInside = child->boundsMouse.inside(localPoint);
        
        if (isInside || type == AppEventType::MOUSE_MOVED) {
            // Pass the event to the child
            bool childConsumed = child->handleRoutedMouseEvent(type, localPoint, button);
            
            // Mark as consumed if any child consumes the event
            if (childConsumed) {
                consumed = true;
                
                // If we're not sending to all components, we can stop here
                if (!sendToAll) {
                    return true;
                }
            }
        }
    }
    
    return consumed;
}

bool NfPanel::handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) {
    // First try to route the event to children
    if (routeMouseEvent(type, localPoint, button)) {
        return true;
    }
    
    // If children didn't handle it, process the event here
    switch (type) {
        case AppEventType::MOUSE_PRESSED:
            if (boundsMouse.inside(localPoint)) {
                if (!nodeIsFocused) {
                    nfUI::NfEventManager::getEventManager().emit("node_focus", _name);
                    // markDimensionsDirty();  // Mark dimensions as dirty when focus changes
                }
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
                setDefaultCursor();
                return true;
            } else {
                if (!nodeIsFocused) {
                    parameters.getBool("IsFocused") = false;
                    setDefaultCursor();
                }   
            }
            return false;
            
        case AppEventType::MOUSE_EXITED:
            if (!boundsMouse.inside(localPoint)) {
                parameters.getBool("IsFocused") = false;
                setDefaultCursor();
                return true;
            }
            return false;
            
        default:
            return false;
    }
}

} // namespace nfUI
