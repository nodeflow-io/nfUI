//
//  NfBoxxer.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NfBoxxer.hpp"
#include "NfSelection.hpp"  // Include for dynamic_cast to NfSelection

namespace nfUI {

// Initialize static variable
bool NfBoxxer::showDebugBounds = false;

NfBoxxer::NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue)
    : NfUIElement(config, std::move(initialValue), name)
    , _config(config)
    , _name(name)
    , _firstRender(true)
    , _transformationDirty(true)
    , _childrenTransformationDirty(true)
    , nodeIsFocused(false)
{
    // Initialize bounds and boundsMouse from config
    bounds = config.bounds;
    boundsMouse = config.bounds;
    
    // Force an initial bounds update
    updateGlobalBounds();
}

void NfBoxxer::updateGlobalBounds() {
    // Skip update if not dirty (optimization)
    if (!_transformationDirty) return;
    
    // Start with local bounds
    if (isRoot()) {
        boundsMouse = bounds;
    } 
    
    // Apply absolute positioning if needed
    if (_config.isAbsolutePosition && !isRoot()) {
        boundsMouse.x += bounds.x;
        boundsMouse.y += bounds.y;
    }
    
    // Apply margins
    if (_config.marginLeft || _config.marginTop) {
        boundsMouse.x += _config.marginLeft;
        boundsMouse.y += _config.marginTop;
    }
    
    // If root node, ensure all children have their local bounds set
    if (this->isRoot()) {
        for (auto& child : children) {
            child->boundsMouse = child->bounds;
        }
    }
    
    // Mark children transformations as clean before processing them
    _childrenTransformationDirty = false;
    
    // Update this element's bounds and all its children
    updateChildrenBounds();
    
    // Now mark this element's transformation as clean
    _transformationDirty = false;
}

void NfBoxxer::updateChildrenBounds() {
    float yOffset = 0;
    
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        
        // Get child dimensions
        float childWidth, childHeight;
        this->getChildDimensions(child, childWidth, childHeight);
        
        // Reset child bounds to local space
        child->boundsMouse = child->bounds;
        
        // Apply all transformations to get global coordinates
        child->boundsMouse.x = this->boundsMouse.x + _config.paddingLeft;
        child->boundsMouse.y = this->boundsMouse.y + _config.paddingTop + yOffset;
        
        // Ensure child boundsMouse has correct dimensions
        // child->boundsMouse.width = childWidth;
        child->boundsMouse.height = childHeight;
        
        if (_config.isDebug) {
            std::cout << "Child " << child->_name << " boundsMouse: " 
                      << child->boundsMouse.x << "," << child->boundsMouse.y 
                      << " w:" << child->boundsMouse.width 
                      << " h:" << child->boundsMouse.height << std::endl;
        }
        
        // Recursively update this child's children if it's a NfBoxxer
        auto childBoxer = dynamic_cast<NfBoxxer*>(child.get());
        if (childBoxer) {
            // Force the child to update its bounds
            childBoxer->_transformationDirty = true;
            childBoxer->updateGlobalBounds();
        }
        
        // Move offset for next child
        yOffset += childHeight;
    }
    
    // Update parent's boundsMouse height to encompass all children
    // Make sure to include the element's original height if it has intrinsic content
    float contentHeight = bounds.height;
    float childrenHeight = _config.paddingTop + yOffset + _config.paddingBottom;
    
    // Use the larger of the two - either the element's own content or its children
    this->boundsMouse.height = std::max(contentHeight, childrenHeight);
    
    if (_config.isDebug) {
        std::cout << "Parent " << _name << " final boundsMouse height: " << this->boundsMouse.height << std::endl;
    }
}

void NfBoxxer::update() {
    // Perform any time-based state updates for this component
    
    // This method is intended to be overridden by derived classes
    // to implement specific update logic for animations, transitions,
    // or other time-dependent behaviors
    
    // After updating this component, update all children
    updateChildren();
}

void NfBoxxer::updateChildren() {
    // Update all children
    for (auto& child : children) {
        auto boxer = dynamic_cast<NfBoxxer*>(child.get());
        if (boxer) {
            boxer->update();
        }
    }
}

void NfBoxxer::markTransformationDirty(bool includeChildren) {
    _transformationDirty = true;
    
    if (includeChildren) {
        _childrenTransformationDirty = true;
        
        // Propagate to children
        for (auto& child : children) {
            auto childBoxer = dynamic_cast<NfBoxxer*>(child.get());
            if (childBoxer) {
                childBoxer->markTransformationDirty(true);
            }
        }
    }
}

void NfBoxxer::setPosition(const ofPoint& position) {
    if (bounds.x != position.x || bounds.y != position.y) {
        NfUIElement::setPosition(position);
        markTransformationDirty();
    }
}

void NfBoxxer::setSize(float width, float height) {
    if (bounds.width != width || bounds.height != height) {
        bounds.width = width;
        bounds.height = height;
        _config.bounds.width = width;
        _config.bounds.height = height;
        markTransformationDirty();
        markDimensionsDirty();
    }
}

void NfBoxxer::drawMouseBounds() {
    // Save previous color
    ofColor prevColor = ofGetStyle().color;
    
    // Draw this element's boundsMouse with semi-transparent color
    ofSetColor(255, 0, 0, 100); // Red with alpha
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawRectangle(boundsMouse);
    
    // Draw padding area if there is significant padding
    if (_config.paddingLeft > 2 || _config.paddingTop > 2 || 
        _config.paddingRight > 2 || _config.paddingBottom > 2) {
        
        // Calculate inner rectangle (content area)
        ofRectangle contentArea = boundsMouse;
        contentArea.x += _config.paddingLeft;
        contentArea.y += _config.paddingTop;
        contentArea.width -= (_config.paddingLeft + _config.paddingRight);
        contentArea.height -= (_config.paddingTop + _config.paddingBottom);
        
        // Draw padding area with different color - subtler visualization
        ofSetColor(255, 165, 0, 70); // Orange with low alpha
        ofNoFill();
        ofSetLineWidth(1);
        ofDrawRectangle(contentArea);
    }
    
    // Draw a small label with the element name
    ofSetColor(255, 0, 0, 200);
    ofDrawBitmapString(_name, boundsMouse.x, boundsMouse.y - 5);
    
    // Restore previous color and fill settings
    ofSetColor(prevColor);
    ofFill();
}

void NfBoxxer::drawChildrenMouseBounds() {
    // Draw bounds for all children
    for (auto& child : children) {
        // Draw child's boundsMouse
        ofColor prevColor = ofGetStyle().color;
        
        // Use a different color for each level in the hierarchy
        ofSetColor(0, 255, 0, 100); // Green with alpha
        ofNoFill();
        ofSetLineWidth(1);
        ofDrawRectangle(child->boundsMouse);
        
        // Draw a small label with the child name
        ofSetColor(0, 255, 0, 200);
        ofDrawBitmapString(child->_name, child->boundsMouse.x, child->boundsMouse.y - 5);
        
        // Restore previous color and fill settings
        ofSetColor(prevColor);
        ofFill();
        
        // Recursively draw bounds for this child's children if it's a NfBoxxer
        auto childBoxer = dynamic_cast<NfBoxxer*>(child.get());
        if (childBoxer) {
            childBoxer->drawChildrenMouseBounds();
        }
    }
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
        _firstRender = false;
    }
    
    // Update bounds if needed
    if (_transformationDirty) {
        updateGlobalBounds();
    }
    
    // Draw debug mouse bounds if enabled
    if (showDebugBounds) {
        drawMouseBounds();
        drawChildrenMouseBounds();
    }
    
    // Start the drawing transform stack - NOTE: derived classes will continue this stack
    ofPushMatrix();
    
    // Apply transformations for rendering (boundsMouse calculations already done)
    if (_config.isAbsolutePosition) {
        ofTranslate(bounds.x, bounds.y);
    }
    
    if (_config.marginLeft || _config.marginTop) {
        ofTranslate(_config.marginLeft, _config.marginTop);
    }
    
    if (_config.isDebug) {
        std::cout << "Boxxer: " << _name << " mB: " << boundsMouse.x << " " << boundsMouse.y << std::endl;
    }
    
    // NOTE: We intentionally DO NOT pop the matrix here
    // Derived classes will call NfBoxxer::draw(), then draw their own content,
    // and finally pop the matrix themselves
    
    // THIS COMMENT IS IMPORTANT:
    // If you are implementing a derived class and call NfBoxxer::draw(),
    // you MUST call ofPopMatrix() at the end of your draw() method!
}

void NfBoxxer::drawChildren(const float& paddingLeft, const float& paddingTop) {
    ofPushMatrix();
    
    // Apply padding translation
    ofTranslate(paddingLeft, paddingTop);
    
    // Track current vertical position
    float yOffset = 0;
    
    // Process all children - first pass for normal elements
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        
        // Get child dimensions
        float childWidth, childHeight;
        this->getChildDimensions(child, childWidth, childHeight);
        
        // Position for current child (in the parent's coordinate system)
        ofPushMatrix();
        ofTranslate(0, yOffset);
        
        // Draw the child (bounds already updated in updateGlobalBounds)
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
            
            ofPushMatrix();
            
            // For proper positioning, we need to locate the dropdown precisely
            // Use pre-calculated positions
            float xPos = child->boundsMouse.x - this->boundsMouse.x - paddingLeft;
            
            // Get the dropdown offset from the selection element
            float dropdownOffset = selectionChild->getDropdownOffset();
            
            // Position the floating element
            ofTranslate(xPos, childYOffset + dropdownOffset);
            
            // Draw just the dropdown portion - the dropdown itself knows its correct position
            selectionChild->drawDropdown();
            
            ofPopMatrix();
        }
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
            // No coordinate transformation - pass global coordinates directly
            if (selectionChild->isPointInFloatingElement(globalPoint)) {
                // Delegate event handling to the floating element with global coordinates
                return selectionChild->handleFloatingElementEvent(type, globalPoint, button);
            }
        }
    }
    return false;  // No floating element handled the event
}

} // namespace nfUI
