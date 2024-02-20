//
//  nfUIElement.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 16.02.24.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "ofMain.h"
#include "../API/ValueType.hpp";
#include <limits>

// Constants
namespace nfUI {
// Define upper clamp limits as constants
const float MAX_PADDING = 10000.0f;
const float MAX_MARGIN = 10000.0f;
const float MAX_BORDER_SIZE = 10000.0f;


struct NfUIConfig {
    ofColor backgroundColor;
    ofColor textColor;
    ofColor borderColor;
    ofColor focusColor;
    ofColor focusBackgroundColor;
    float paddingTop;
    float paddingRight;
    float paddingBottom;
    float paddingLeft;
    float marginTop;
    float marginRight;
    float marginBottom;
    float marginLeft;
    float borderSize;
    float width;
    float height;
    float minWidth;
    float minHeight;
    bool isFocused;
    ofRectangle bounds;
    uint32_t maxTextLength;
    bool textIsPassword;
    
    NfUIConfig() {
        // Set default values for the config
        backgroundColor = ofColor::gray;
        textColor = ofColor::white;
        borderColor = ofColor::white;
        focusColor = ofColor::yellow;
        focusBackgroundColor = ofColor::lightBlue;
        paddingTop = 3.0f;
        paddingRight = 10.0f;
        paddingBottom = 3.0f;
        paddingLeft = 10.0f;
        marginTop = 3.0f;
        marginRight = 10.0f;
        marginBottom = 3.0f;
        marginLeft = 10.0f;
        borderSize = 1.0f;
        width = 100.0f;
        height = 20.0f;
        minWidth = 50.0f;
        minHeight = 20.0f;
        isFocused = false;
        bounds = ofRectangle (0,0, 100.0f, 20.0f);
        maxTextLength = 255;
        textIsPassword = false;
    }
};


class Offsets {
public:
    ofParameterGroup parameters;
    ofParameter<float> top;
    ofParameter<float> right;
    ofParameter<float> bottom;
    ofParameter<float> left;

    Offsets(const std::string& groupName, float topValue = 0, float rightValue = 0, float bottomValue = 0, float leftValue = 0)
        : top(groupName + " Top", topValue, 0, std::numeric_limits<float>::max()),
          right(groupName + " Right", rightValue, 0, std::numeric_limits<float>::max()),
          bottom(groupName + " Bottom", bottomValue, 0, std::numeric_limits<float>::max()),
          left(groupName + " Left", leftValue, 0, std::numeric_limits<float>::max()) {
        parameters.setName(groupName);
        parameters.add(top);
        parameters.add(right);
        parameters.add(bottom);
        parameters.add(left);
    }

    // Getters
    float getTop() const { return top; }
    float getRight() const { return right; }
    float getBottom() const { return bottom; }
    float getLeft() const { return left; }

    // Setters
    void set(float value) {
        setTop(value);
        setRight(value);
        setBottom(value);
        setLeft(value);
    }
    void setTop(float value) { top = std::min(value, std::numeric_limits<float>::max()); }
    void setRight(float value) { right = std::min(value, std::numeric_limits<float>::max()); }
    void setBottom(float value) { bottom = std::min(value, std::numeric_limits<float>::max()); }
    void setLeft(float value) { left = std::min(value, std::numeric_limits<float>::max()); }
};

class UIEventArgs : public ofEventArgs {
    // Add any data members if needed
public:
    UIEventArgs() {}  // Default constructor
};

class UIElement {
public:
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

    ofRectangle bounds;
    
    // event handling
    ofEvent<UIEventArgs> clicked;
    
    
    // Constructor with Config parameter
    UIElement(const NfUIConfig& config = NfUIConfig(), const std::string& elementName = "DefaultName")
        :   padding(elementName + " Padding",
                    config.paddingTop,
                    config.paddingRight,
                    config.paddingBottom,
                    config.paddingLeft),
          margin(elementName + " Margin",
                 config.marginTop,
                 config.marginRight,
                 config.marginBottom,
                 config.marginLeft) {
       
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
        // bounds.set("Bounds", config.bounds);
        
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
    
    // Method to set the type
    
    void setValueType(nfAPI::ValueType type) {
        valueType = type;
    }
     
    // Getter and setter methods for other properties
    ofColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor(const ofColor& value) { backgroundColor = value; }
    
    ofColor getTextColor() const { return textColor; }
    void setTextColor(const ofColor& value) { textColor = value; }
    
    ofColor getBorderColor() const { return borderColor; }
    void setBorderColor(const ofColor& value) { borderColor = value; }
    
    ofColor getFocusColor() const { return focusColor; }
    void setFocusColor(const ofColor& value) { focusColor = value; }
    
    ofColor getFocusBackgroundColor() const { return focusBackgroundColor; }
    void setFocusBackgroundColor(const ofColor& value) { focusBackgroundColor = value; }
    
    // Getter and setter methods for padding properties
    float getPaddingTop() const { return padding.getTop(); }
    void setPaddingTop(float value) { padding.setTop(value); }

    float getPaddingRight() const { return padding.getRight(); }
    void setPaddingRight(float value) { padding.setRight(value); }

    float getPaddingBottom() const { return padding.getBottom(); }
    void setPaddingBottom(float value) { padding.setBottom(value); }

    float getPaddingLeft() const { return padding.getLeft(); }
    void setPaddingLeft(float value) { padding.setLeft(value); }
    
    // Getter and setter methods for margin properties
    float getMarginTop() const { return margin.getTop(); }
    void setMarginop(float value) { margin.setTop(value); }

    float getMarginRight() const { return margin.getRight(); }
    void setMarginRight(float value) { margin.setRight(value); }

    float getMarginBottom() const { return margin.getBottom(); }
    void setMarginBottom(float value) { margin.setBottom(value); }

    float getMarginLeft() const { return margin.getLeft(); }
    void setMarginLeft(float value) { margin.setLeft(value); }
    

    float getBorderSize() const { return borderSize; }
    void setBorderSize(float value) { borderSize = ofClamp(value, 0.0f, MAX_BORDER_SIZE); }
    
    bool getIsFocused() const { return isFocused; }
    void setIsFocused(bool value) { isFocused = value; }
    
    
    float getWidth() const { return width; }
    void setWidth(float value) { width = ofClamp(value, minWidth, numeric_limits<float>::max()); }
    
    float getHeight() const { return height; }
    void setHeight(float value) { height = ofClamp(value, minHeight, numeric_limits<float>::max()); }
    
    float getMinWidth() const { return minWidth; }
    void setMinWidth(float value) { minWidth = value; }
    
    float getMinHeight() const { return minHeight; }
    void setMinHeight(float value) { minHeight = value; }
    
    // Add getter and setter methods for other properties as needed
    
    
    virtual void setup() {
    }
    
    virtual ofRectangle getBounds() {
        return this->bounds;
    }
    
    virtual void setBounds(ofRectangle bounds) {
        this->bounds = bounds;
    }
    
    // Draw method
    virtual void draw() {
        // Draw border
        ofSetColor(borderColor);
        ofDrawRectangle(x, y, width, height);
        
        // Draw background
        ofSetColor(isFocused ? focusBackgroundColor : backgroundColor);
        ofDrawRectangle(x + borderSize, y + borderSize, width - 2 * borderSize, height - 2 * borderSize);
        
        // Draw text
        ofSetColor(textColor);
        ofDrawBitmapString("Your Text", x + padding.getLeft() + borderSize, y + height / 2);
        
        // Add more drawing logic as needed
    }
    
    // Event handling
    virtual void mousePressed(int mouseX, int mouseY) {
        if (isMouseInside(mouseX, mouseY)) {
            isFocused = true;
        } else {
            isFocused = false;
        }
    }
    
    // Event handling for mouse movement
    virtual void mouseMoved(ofMouseEventArgs& args) {
        // Check if the mouse is inside the bounds of the text input field
        if (bounds.inside(args.x, args.y)) {
            // Optionally, you can change the cursor to indicate the field is interactable
            // or highlight the field in some manner.
            // This is just an example and may depend on your specific UI requirements.
            // For instance:
            // ofSetCursor(OF_CURSOR_IBEAM);
            isFocused = true;
            // Here you can also set a flag that you're hovering over the field
            // if you have a visual indication for it.
        } else {
            // Reset to default cursor if you changed it above
            // ofSetCursor(OF_CURSOR_ARROW);
            isFocused = false;
            // Reset any hover state you might have set
        }
    }
    
private:
    // Internal properties like position (x, y) can be managed privately
    float x;
    float y;
    float contentWidth;
    float contentHeight;
    
    // Helper method to check if the mouse is inside the element
    virtual bool isMouseInside(int mouseX, int mouseY) {
        return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    }
    
    // virtual void    mousePressed(ofMouseEventArgs& args);
    // virtual void    mouseDragged(ofMouseEventArgs& args);
    // virtual void    mouseReleased(ofMouseEventArgs& args);
};

}


#endif /* UIElement_hpp */
