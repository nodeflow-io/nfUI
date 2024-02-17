//
//  nfUIElement.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 16.02.24.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "ofMain.h"

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
    float padding;
    float margin;
    float borderSize;
    float width;
    float height;
    float minWidth;
    float minHeight;
    bool isFocused;
    ofRectangle bounds;
    
    NfUIConfig() {
        // Set default values for the config
        backgroundColor = ofColor::gray;
        textColor = ofColor::white;
        borderColor = ofColor::white;
        focusColor = ofColor::yellow;
        focusBackgroundColor = ofColor::lightBlue;
        padding = 10.0f;
        margin = 5.0f;
        borderSize = 1.0f;
        width = 100.0f;
        height = 20.0f;
        minWidth = 50.0f;
        minHeight = 20.0f;
        isFocused = false;
        bounds = ofRectangle (0,0, 100.0f, 20.0f);
    }
};

class UIElement {
public:
    ofParameterGroup parameters;
    ofParameter<ofColor> backgroundColor;
    ofParameter<ofColor> textColor;
    ofParameter<ofColor> borderColor;
    ofParameter<ofColor> focusColor;
    ofParameter<ofColor> focusBackgroundColor;
    ofParameter<float> padding;
    ofParameter<float> margin;
    ofParameter<float> borderSize;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> minWidth;
    ofParameter<float> minHeight;
    ofParameter<bool> isFocused;
    ofParameter<ofRectangle> bounds;
    
    // Constructor with Config parameter
    UIElement(const NfUIConfig& config = NfUIConfig()) {
        // Set default values from the config
        backgroundColor.set("Background Color", config.backgroundColor);
        textColor.set("Text Color", config.textColor);
        borderColor.set("Border Color", config.borderColor);
        focusColor.set("Focus Color", config.focusColor);
        focusBackgroundColor.set("Focus Background Color", config.focusBackgroundColor);
        padding.set("Padding", config.padding, 0.0f, 20.0f);
        margin.set("Margin", config.margin, 0.0f, 50.0f);
        borderSize.set("Border Size", config.borderSize, 0.0f, 10.0f);
        width.set("Width", config.width, config.minWidth, numeric_limits<float>::max());
        height.set("Height", config.height, config.minHeight, numeric_limits<float>::max());
        minWidth.set("Min Width", config.minWidth);
        minHeight.set("Min Height", config.minHeight);
        isFocused.set("Is Focused", config.isFocused);
        bounds.set("Bounds", config.bounds);
        
        // Add parameters to the group
        parameters.setName("UI Element Parameters");
        parameters.add(backgroundColor);
        parameters.add(textColor);
        parameters.add(borderColor);
        parameters.add(focusColor);
        parameters.add(focusBackgroundColor);
        parameters.add(padding);
        parameters.add(margin);
        parameters.add(borderSize);
        parameters.add(width);
        parameters.add(height);
        parameters.add(minWidth);
        parameters.add(minHeight);
        parameters.add(isFocused);
        parameters.add(bounds);
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
    
    float getPadding() const { return padding; }
    void setPadding(float value) { padding = ofClamp(value, 0.0f, MAX_PADDING); }
    
    float getMargin() const { return margin; }
    void setMargin(float value) { margin = ofClamp(value, 0.0f, MAX_MARGIN); }
    
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
        ofDrawBitmapString("Your Text", x + padding + borderSize, y + height / 2);
        
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
    
private:
    // Internal properties like position (x, y) can be managed privately
    float x;
    float y;
    
    // Helper method to check if the mouse is inside the element
    virtual bool isMouseInside(int mouseX, int mouseY) {
        return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    }
};

}
/*

 Usage
 
// ofApp class for handling events
class ofApp : public ofBaseApp {
public:
    UIElement uiElement;

    void setup() {
        ofSetBackgroundColor(255);
    }

    void draw() {
        uiElement.draw();
    }

    void mousePressed(int x, int y, int button) {
        uiElement.mousePressed(x, y);
    }

    // GUI event handling
    void keyPressed(int key) {
        if (key == 'g' || key == 'G') {
            // Toggle visibility of the GUI
            uiElement.parameters.getGroup("UI Element Parameters").toggleVisible();
        }
    }
};

int main() {
    ofSetupOpenGL(800, 600, OF_WINDOW);
    ofRunApp(new ofApp());
}
*/


#endif /* UIElement_hpp */
