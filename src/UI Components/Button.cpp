//
//  Button.cpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 17.02.24.
//

#include "Button.hpp"

namespace nfUI {
// Constructor for ofxTextInputField
Button::Button(const NfUIConfig& config) : UIElement(config) {
    parameters.setName("Button");
    text = "Submit Solve";
    fontRef = NULL;
    isEnabled = false;
    bounds = ofRectangle(0,0,100,22);
    mouseDownInRect = false;
    fontRef = new ofxTextInput::BitmapFontRenderer();
}

Button::Button(const NfUIConfig& config, const std::string& elementName) : UIElement(config) {
    parameters.setName(elementName);
    text = "Submit Solve";
    fontRef = NULL;
    isEnabled = false;
    bounds = ofRectangle(0,0,100,22);
    mouseDownInRect = false;
    fontRef = new ofxTextInput::BitmapFontRenderer();
}

Button::~Button(){
    if(isEnabled){
        disable();
    }
    
}

void Button::setup(){
    enable();
}


void Button::enable(){
    if(!isEnabled){
        ofAddListener(ofEvents().mousePressed, this, &Button::mousePressed);
        // ofAddListener(ofEvents().mouseDragged, this, &Button::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &Button::mouseReleased);
        isEnabled = true;
    }
}

void Button::disable(){
    if(isEnabled){
        ofRemoveListener(ofEvents().mousePressed, this, &Button::mousePressed);
        // ofRemoveListener(ofEvents().mouseDragged, this, &Button::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &Button::mouseReleased);
        isEnabled = false;
    }
}

void Button::setFont(OFX_TEXTFIELD_FONT_RENDERER& font) {
    fontRef = dynamic_cast<ofxTextInput::FontRenderer*>(&font);
    
    // Check if the dynamic cast was successful
    if (!fontRef) {
        // Handle the case where the cast failed (e.g., log an error)
        // Note: This assumes that `ofxTextInput::FontRenderer` is a base class of `OFX_TEXTFIELD_FONT_RENDERER`.
    }
}

bool Button::getIsEnabled() {
    return isEnabled;
}

void Button::draw() {
    // Draw border
    ofSetColor(borderColor);
    ofDrawRectangle(bounds.x, bounds.y, width, height);
    
    // Draw background
    ofSetColor(isFocused ? focusBackgroundColor : backgroundColor);
    ofDrawRectangle(bounds.x + borderSize, bounds.y + borderSize, width - 2 * borderSize, height - 2 * borderSize);
    
    // Draw text
    ofSetColor(textColor);
    ofPushMatrix();
    ofTranslate(bounds.x, bounds.y);
    // TODO: padding top , bottom , etc
    fontRef->drawString(text, this->padding.getLeft(), fontRef->getLineHeight()+this->padding.getTop());
    ofPopMatrix();
}

void Button::clear() {
    // Clear any internal state, if needed
}

void Button::keyPressed(ofKeyEventArgs& a) {
    // Handle key pressed event for the button, if needed
}

void Button::keyReleased(ofKeyEventArgs& a) {
    // Handle key released event for the button, if needed
}

void Button::mousePressed(ofMouseEventArgs& args) {
    // Handle mouse pressed event for the button, if needed
    mouseDownInRect = bounds.inside(args.x, args.y);
    if(mouseDownInRect) {

    }
}

void Button::mouseReleased(ofMouseEventArgs& args) {
    // Handle mouse released event for the button, if needed
    mouseDownInRect = bounds.inside(args.x, args.y);
    if (mouseDownInRect) {
        UIEventArgs eventArgs;
        ofNotifyEvent(clicked, eventArgs, this);
    }
}

}
