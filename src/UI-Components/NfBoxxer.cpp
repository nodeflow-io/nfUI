//
//  NfBoxxer.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NfBoxxer.hpp"
#include "NfSelection.hpp"  // Include for dynamic_cast to NfSelection

namespace nfUI {

NfBoxxer::NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue)
    : NfUIElement(config, std::move(initialValue), name)
    , _config(config)
    , _name(name)
    , _firstRender(true)
    , nodeIsFocused(false)
{
    // Your initialization code here
}

void NfBoxxer::draw() {
    if (_firstRender) {
        if (_config.isDebug) {
            std::cout << "Boxxer: First render of " << _name << std::endl;
            NFValue* valueRawPtr = this->getValue();
            if (valueRawPtr != nullptr) {
                std::string valueAsString = valueRawPtr->toString();
                std::cout << "Boxxer: Value as string: " << valueAsString << std::endl;
            } else {
                std::cout << "Boxxer: No value available." << std::endl;
            }
        }
    }
    
    // this is used for keeping track of the bounds for mouse interactions
    // If we are drawing the root element we reset it for all children too
    if (this->isRoot()) {
        for (size_t i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            child->boundsMouse = child->bounds;
        }
    }
    
    // decide wheter we need to translate to an absolute position
    if (_config.isAbsolutePosition) {
        ofTranslate(bounds.x, bounds.y);
        // if this is not the root element we need to translate
        // the mousebounds to its new absolute position
        // because mousevents are happening in absolute coordinates
        if (!this->isRoot()) {
            translateBounds(boundsMouse, bounds.x, bounds.y, _name);
        }
        if (_config.isDebug) {
            std::cout << "Boxxer: " << _name << " absolute position: " << bounds.x << "," << bounds.y << std::endl;
        }
    }
    
    // decide wheter we need to translate the margins
    if (_config.marginTop || _config.marginLeft) {
        ofTranslate(_config.marginLeft, _config.marginTop);
        translateBounds(boundsMouse, _config.marginLeft, _config.marginTop, _name);
        if (_config.isDebug) {
            std::cout << "Boxxer: " << _name << " margin: " << _config.marginLeft << "," << _config.marginTop << std::endl;
        }
    }
    
    if (_config.isDebug) {
        std::cout << "Boxxer: " << _name << " mB: " << boundsMouse.x << " " << boundsMouse.y << std::endl;
    }
    
    // After the first render, set the flag to false
    if (_firstRender) {
        _firstRender = false;
    }
}

void NfBoxxer::drawChildren(const float& paddingLeft, const float& paddingTop) {
    ofPushMatrix();
    
    // Step 1: Apply padding translation
    ofTranslate(paddingLeft, paddingTop);
    
    // Track current vertical position
    float yOffset = 0;
    
    // Step 2: Process all children - first pass for normal elements
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        
        // Get child dimensions
        float childWidth, childHeight;
        this->getChildDimensions(child, childWidth, childHeight);
        
        // Position for current child (in the parent's coordinate system)
        ofPushMatrix();
        ofTranslate(0, yOffset);
        
        // Update child's boundsMouse to reflect its absolute position
        // First reset to avoid accumulated translations
        child->boundsMouse = child->bounds;
        
        // Apply all transformations to get global coordinates
        child->boundsMouse.x = this->boundsMouse.x + paddingLeft;
        child->boundsMouse.y = this->boundsMouse.y + paddingTop + yOffset;
        
        if (_config.isDebug) {
            std::cout << "Child " << child->_name << " boundsMouse: " 
                      << child->boundsMouse.x << "," << child->boundsMouse.y 
                      << " w:" << child->boundsMouse.width 
                      << " h:" << child->boundsMouse.height << std::endl;
        }
        
        // Draw the child
        child->draw();
        
        ofPopMatrix();
        
        // Move offset for next child
        yOffset += childHeight;
    }
    
    // Second pass: draw floating elements (like dropdowns) on top of everything
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        
        // Check if this child has floating elements (like an open dropdown)
        auto selectionChild = dynamic_cast<NfSelection*>(child.get());
        if (selectionChild && selectionChild->hasFloatingElement()) {
            // Calculate vertical position for the floating element
            float childYOffset = 0;
            for (size_t j = 0; j < i; j++) {
                float w, h;
                this->getChildDimensions(children[j], w, h);
                childYOffset += h;
            }
            
            // We need to position the dropdown exactly where the selection element is
            // This means using the same translation that was applied during the first pass
            
            ofPushMatrix();
            
            // For proper positioning, we need to add the same offsets as we did during the first pass
            // Child's position relative to parent
            float xPos = child->boundsMouse.x - this->boundsMouse.x - paddingLeft;
            
            // Use exact position to ensure alignment
            ofTranslate(xPos, childYOffset);
            
            // Draw just the dropdown portion - the dropdown itself knows its correct position
            // relative to its parent element (the selection box)
            selectionChild->drawDropdown();
            
            ofPopMatrix();
        }
    }
    
    // Update parent's boundsMouse height to encompass all children
    this->boundsMouse.height = paddingTop + yOffset + _config.paddingBottom;
    
    if (_config.isDebug) {
        std::cout << "Parent " << _name << " final boundsMouse height: " << this->boundsMouse.height << std::endl;
    }
    
    ofPopMatrix();
}

void NfBoxxer::focus() {
    nodeIsFocused = true;
}

void NfBoxxer::setListenerID(ListenerID id) {
    listenerID = id;
}

NfBoxxer::ListenerID NfBoxxer::getListenerID() const {
    return listenerID;
}

bool NfBoxxer::routeEventToFloatingElements(AppEventType type, const ofPoint& globalPoint, int button) {
    // Check if we have any children with floating elements that might handle this event
    for (auto& child : children) {
        // Check if this child has a floating element and if the point is inside it
        auto selectionChild = dynamic_cast<NfSelection*>(child.get());
        if (selectionChild && selectionChild->hasFloatingElement()) {
            // Transform global coordinates to the child's local coordinates
            ofPoint localPoint = globalPoint;
            
            // Adjust coordinates based on child's position in parent
            localPoint.x -= child->boundsMouse.x;
            localPoint.y -= child->boundsMouse.y;
            
            if (selectionChild->isPointInFloatingElement(localPoint)) {
                // Delegate event handling to the floating element with transformed coordinates
                return selectionChild->handleFloatingElementEvent(type, localPoint, button);
            }
        }
    }
    return false;  // No floating element handled the event
}

} // namespace nfUI
