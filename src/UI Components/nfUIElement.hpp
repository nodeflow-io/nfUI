//
//  nfUIElement.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef nfUIElement_hpp
#define nfUIElement_hpp

#include "ofMain.h"
#include "NfUIConfig.hpp"
#include "../API/ValueType.hpp"
#include "NFValue.hpp"

namespace nfUI {

class NfUIElement : public std::enable_shared_from_this<NfUIElement> {
    
private:
    std::unique_ptr<NFValue> value; // Smart pointer to NFValue
public:
    std::weak_ptr<NfUIElement> parent; // Weak pointer to the parent element
    std::vector<std::shared_ptr<NfUIElement>> children; // List of children elements
    NfUIConfig _config; // Hold configuration settings for this UI element
    
    nfAPI::ValueType valueType;
    ofParameterGroup parameters;
    ofParameter<ofColor> backgroundColor;
    ofParameter<ofColor> textColor;
    ofParameter<ofColor> borderColor;
    ofParameter<ofColor> focusColor;
    ofParameter<ofColor> focusBackgroundColor;
    Offsets padding;
    Offsets margin;
    ofParameter<float> borderSize;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> minWidth;
    ofParameter<float> minHeight;
    ofParameter<float> maxWidth;
    ofParameter<float> maxHeight;
    ofParameter<bool> isFocused;
    ofParameter<bool> isVisible;
    std::string text;
    ofParameter<uint32_t> maxTextLength;
    ofParameter<bool> textIsPassword;
    ofParameter<bool> isAbsolutePosition;
    
    ofRectangle bounds;
    ofRectangle boundsMouse;
    // Constructor with Config parameter
    // NfUIElement(std::unique_ptr<NFValue> initialValue)
    //        : value(std::move(initialValue)) {}
    
    NfUIElement(const NfUIConfig& config = NfUIConfig(), std::unique_ptr<NFValue> initialValue = nullptr, const std::string& elementName = "DefaultName")
    :   value(std::move(initialValue)) ,
    padding(elementName + " Padding",
            config.paddingTop,
            config.paddingRight,
            config.paddingBottom,
            config.paddingLeft),
    margin(elementName + " Margin",
           config.marginTop,
           config.marginRight,
           config.marginBottom,
           config.marginLeft) {
        
        // Check if value is not nullptr and then get its type
        if (value) {
            valueType = value->getType();
        } else {
            valueType = nfAPI::ValueType::NotSet;
        }
        
        _config = config;
        // Set default values from the config
        backgroundColor.set("BackgroundColor", config.backgroundColor);
        textColor.set("TextColor", config.textColor);
        borderColor.set("BorderColor", config.borderColor);
        focusColor.set("FocusColor", config.focusColor);
        focusBackgroundColor.set("FocusBackgroundColor", config.focusBackgroundColor);
        borderSize.set("BorderSize", config.borderSize, 0.0f, 10.0f);
        width.set("Width", config.width, config.minWidth, numeric_limits<float>::max());
        height.set("Height", config.height, config.minHeight, numeric_limits<float>::max());
        minWidth.set("MinWidth", config.minWidth);
        minHeight.set("MinHeight", config.minHeight);
        isFocused.set("IsFocused", config.isFocused);
        maxTextLength.set("maxTextLength", config.maxTextLength);
        textIsPassword.set("textIsPassword", config.textIsPassword);
        isAbsolutePosition.set("textIsPassword", config.isAbsolutePosition);
        bounds = config.bounds;
        // screen position is altered using ofTranslate / Push & Pop - so we need to track this
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
        // parameters.add(bounds);
    }
    
    // This method returns true if parent is expired, which indicates that
    // there is no parent, making this element the root of the tree.
     // It returns false if parent is not expired, meaning this element
    // has a parent and therefore is not the root.
    bool isRoot() const {
        return parent.expired();
    }
    
    // Function to add a child element
    void addChild(const std::shared_ptr<NfUIElement>& child) {
        children.push_back(child);
        child->parent = shared_from_this();
    }
    
    // Virtual draw function to be overridden
    virtual void draw() = 0;
    
    // Function to set the value with a unique_ptr to NFValue
    void setValue(std::unique_ptr<NFValue> newValue) {
        value = std::move(newValue); // Transfer ownership
    }
    
    // Method to retrieve a raw pointer to NFValue for reading or manipulation
    // Caution: This does not transfer ownership!
    NFValue* getValue() const {
        return value.get();
    }
    
    // Bounding
    void getDimensions(float& width, float& height) {
        float childrenWidth = 0;
        float childrenHeight = 0;
        for (auto& child : this->children) {
            float childHeight;
            this->getChildDimensions(child, childrenWidth, childHeight);
            childrenHeight += childHeight;
        }
        width = childrenWidth + this->_config.paddingLeft + this->_config.paddingRight;
        height = childrenHeight + this->_config.paddingTop + this->_config.paddingBottom;
    }
    
    void getChildDimensions(const std::shared_ptr<NfUIElement>& child, float& width, float& height) {
        float childWidth = 0;
        float childHeight = 0;
        // TODO: add content width and min, max
        childWidth = child->_config.marginLeft +
        child->_config.paddingLeft +
        child->_config.marginRight +
        child->_config.paddingRight +
        child->bounds.width - (_config.paddingLeft + _config.paddingRight);
        
        childHeight += child->_config.marginTop +
        child->_config.paddingTop +
        child->_config.marginTop +
        child->_config.paddingBottom +
        child->_config.marginBottom +
        child->bounds.height - (_config.paddingTop + _config.paddingBottom);
        
        width = childWidth;// + this->_config.paddingLeft + this->_config.paddingRight;
        height = childHeight; // + this->_config.paddingTop + this->_config.paddingBottom;
        
        /*
        std::cout << child->_config.marginTop << " " <<
        child->_config.paddingTop << " " <<
        (child->bounds.height -(_config.paddingTop + _config.paddingBottom)) << " " <<
        child->_config.paddingBottom << " " <<
        child->_config.marginBottom << std::endl;
         */
        
    }
    
    void translateBounds(ofRectangle& boundsref, float x, float y) {
        boundsref.x += x;
        boundsref.y += y;
    }
    
};

} // nfUI
#endif /* nfUIElement_hpp */
