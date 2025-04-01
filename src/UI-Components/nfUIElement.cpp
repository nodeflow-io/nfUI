//
//  nfUIElement.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "nfUIElement.hpp"

namespace nfUI {

NfUIElement::NfUIElement(const NfUIConfig& config, std::unique_ptr<NFValue> initialValue, const std::string& elementName)
    : value(std::move(initialValue))
    , padding(elementName + " Padding",
             config.paddingTop,
             config.paddingRight,
             config.paddingBottom,
             config.paddingLeft)
    , margin(elementName + " Margin",
            config.marginTop,
            config.marginRight,
            config.marginBottom,
            config.marginLeft)
{
    // Check if value is not nullptr and then get its type
    if (value) {
        valueType = value->getType();
    } else {
        valueType = nfAPI::ValueType::NotSet;
    }
    _name = elementName;
    _config = config;
    
    // Set default values from the config
    backgroundColor.set("BackgroundColor", config.backgroundColor);
    textColor.set("TextColor", config.textColor);
    borderColor.set("BorderColor", config.borderColor);
    focusColor.set("FocusColor", config.focusColor);
    focusBackgroundColor.set("FocusBackgroundColor", config.focusBackgroundColor);
    borderSize.set("BorderSize", config.borderSize, 0.0f, 10.0f);
    width.set("Width", config.width, config.minWidth, std::numeric_limits<float>::max());
    height.set("Height", config.height, config.minHeight, std::numeric_limits<float>::max());
    minWidth.set("MinWidth", config.minWidth);
    minHeight.set("MinHeight", config.minHeight);
    isFocused.set("IsFocused", config.isFocused);
    maxTextLength.set("maxTextLength", config.maxTextLength);
    textIsPassword.set("textIsPassword", config.textIsPassword);
    isAbsolutePosition.set("textIsPassword", config.isAbsolutePosition);
    bounds = config.bounds;
    boundsMouse = config.bounds;
    
    // Add parameters to the group
    parameters.setName(elementName);
    parameters.add(backgroundColor);
    parameters.add(textColor);
    parameters.add(borderColor);
    parameters.add(focusColor);
    parameters.add(focusBackgroundColor);
    parameters.add(padding.parameters);
    parameters.add(margin.parameters);
    parameters.add(borderSize);
    parameters.add(width);
    parameters.add(height);
    parameters.add(minWidth);
    parameters.add(minHeight);
    parameters.add(isFocused);
    parameters.add(maxTextLength);
    parameters.add(textIsPassword);
}

bool NfUIElement::isRoot() const {
    return parent.expired();
}

NfUIElement* NfUIElement::findRoot() {
    NfUIElement* current = this;
    while (current->parent.lock() != nullptr) {
        current = current->parent.lock().get();
    }
    return current;
}

void NfUIElement::addChild(const std::shared_ptr<NfUIElement>& child) {
    children.push_back(child);
    child->parent = shared_from_this();
    markDimensionsDirty();
}

void NfUIElement::setValue(std::unique_ptr<NFValue> newValue) {
    value = std::move(newValue);
}

NFValue* NfUIElement::getValue() const {
    return value.get();
}

void NfUIElement::getDimensions(float& width, float& height) {
    // Return cached values if not dirty
    if (!_dimensionsDirty) {
        width = _cachedWidth;
        height = _cachedHeight;
        return;
    }

    float childrenWidth = 0;
    float childrenHeight = 0;
    float childrenWidthMax = 0;
    
    for (const auto& child : children) {
        float childHeight;
        float childWidth;
        this->getChildDimensions(child, childWidth, childHeight);
        childrenWidthMax = std::max(childrenWidthMax, childWidth);
        childrenHeight += childHeight;
    }
    
    // Calculate and cache dimensions
    _cachedWidth = childrenWidthMax + this->_config.paddingLeft + this->_config.paddingRight;
    _cachedHeight = childrenHeight + this->_config.paddingTop + this->_config.paddingBottom;
    _dimensionsDirty = false;
    
    width = _cachedWidth;
    height = _cachedHeight;
}

void NfUIElement::markDimensionsDirty() {
    _dimensionsDirty = true;
    // Propagate dirty state to parent
    if (auto parentPtr = parent.lock()) {
        parentPtr->markDimensionsDirty();
    }
}

void NfUIElement::getPosition(ofPoint& position) {
    NfUIElement* rootElement = this->findRoot();
    position.x = rootElement->boundsMouse.x;
    position.y = rootElement->boundsMouse.y;
}

void NfUIElement::setPosition(const ofPoint& position) {
    NfUIElement* rootElement = this->findRoot();
    float offsetX = position.x - rootElement->bounds.x;
    float offsetY = position.y - rootElement->bounds.y;
    
    rootElement->bounds.x = position.x;
    rootElement->bounds.y = position.y;
    rootElement->_config.bounds.x = position.x;
    rootElement->_config.bounds.y = position.y;
    rootElement->boundsMouse.x = position.x;
    rootElement->boundsMouse.y = position.y;
    
    for (auto& child : rootElement->children) {
        child->bounds.x += offsetX;
        child->bounds.y += offsetY;
        child->boundsMouse.x += offsetX;
        child->boundsMouse.y += offsetY;
    }
}

void NfUIElement::getChildDimensions(const std::shared_ptr<NfUIElement>& child, float& width, float& height) {
    float childWidth = child->_config.marginLeft + child->_config.marginRight + child->_config.contentWidth;
    float childHeight = child->_config.marginTop + child->_config.paddingTop + 
                       child->_config.marginTop + child->_config.paddingBottom + 
                       child->_config.marginBottom + child->_config.contentHeight;
    
    width = childWidth;
    height = childHeight;
}

void NfUIElement::translateBounds(ofRectangle& boundsref, float deltaX, float deltaY, std::string name) {
    boundsref.x += deltaX;
    boundsref.y += deltaY;
    if (_config.isDebug) {
        std::cout << "translateBounds (" << name << "->" << deltaX << "," << deltaY 
                  << "): New boundsMouse = (" << boundsref.x << ", " << boundsref.y << ")" << std::endl;
    }
}

size_t NfUIElement::getChildCountOfRoot() {
    NfUIElement* rootElement = this->findRoot();
    return rootElement->children.size();
}

} // namespace nfUI
