//
//  ofxNodeFlowGUI.cpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 15.02.24.
//

#include "ofxNodeFlowGUI.hpp"

// constructor
ofxNodeFlowGUI::ofxNodeFlowGUI() {
}

// destrutor
ofxNodeFlowGUI::~ofxNodeFlowGUI()  {
}

void ofxNodeFlowGUI::setup() {
    // Load a TrueType font file (replace "your_font.ttf" with the actual filename)
    std::string fontFace = "Roboto-Thin.ttf";
    uint32_t fontSize = 11;
    if (font.loadFont(fontFace, fontSize)) {
        // Font loaded successfully, you can use it now
        ofLogError() << "ofxNodeFlowGUI::setup(): loaded font" << fontFace+ " size: " << fontSize;
    } else {
        // Handle the case where the font failed to load
        ofLogError() << "ofxNodeFlowGUI::setup(): Failed to load font!";
    }
    // Add NFValues to the node with labels
    ofxTextInputField textInputField1;
    ofxTextInputField textInputField2;
    ofxTextInputField textInputField3;
    ofxTextInputField textInputField4;
    ofxTextInputField textInputField5;
    
    textInputFields.push_back(textInputField1);
    textInputFields.push_back(textInputField2);
    textInputFields.push_back(textInputField3);
    textInputFields.push_back(textInputField4);
    textInputFields.push_back(textInputField5);
    
    // Add NFValues to the node with labels and set up textInputFields
    nfNode.addNFValue<DoubleNFValue, double>("Stepper", 3.14, textInputFields[0], 600, 20, 120, 20, font);
    nfNode.addNFValue<IntNFValue, int>("Acclleration", 42, textInputFields[1], 600, 40, 120, 20, font);
    nfNode.addNFValue<BoolNFValue, bool>("Reset", false, textInputFields[2], 600, 60, 120, 20, font);
    nfNode.addNFValue<StringNFValue, std::string>("Mode", "Forward", textInputFields[3], 600, 80, 120, 20, font);
    nfNode.addNFValue<BoolNFValue, bool>("isReady", true, textInputFields[4], 600, 100, 120, 20, font);
}

void ofxNodeFlowGUI::drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    // Set color to blue (filled)
    ofSetColor(128, 128, 128);
    // Draw a filled rectangle at position (100, 100) with a width of 200 and height of 150
    ofDrawRectangle(x, y, width, height);
    
    // Set color to black (outline)
    ofSetColor(255);
    // Draw the same rectangle with no fill to create the outline
    ofNoFill();
    ofDrawRectangle(x, y, width, height);
    ofDrawRectangle(x + width, y, width, height);
    ofFill(); // Restore fill mode for subsequent drawings
}

void ofxNodeFlowGUI::drawValue() {
    ofBackground(0);
    ofSetColor(255);
    
    // Access and modify NFValues in the order they were added
    const std::vector<NFValue*>& drawOrder = nfNode.getDrawOrder();
    size_t indexCounter=0;
    for (const auto& nfValue : drawOrder) {
        ofRectangle initialPosition = textInputFields[indexCounter].bounds;
        ofRectangle labelPosition = textInputFields[indexCounter].bounds;
        ofRectangle valuePosition = textInputFields[indexCounter].bounds;
        this->drawPanel(labelPosition.x, labelPosition.y, labelPosition.width, labelPosition.height);
        ofSetColor(255);
        // adjust position for font rendering
        labelPosition.x += 10;
        labelPosition.y += 14;
        valuePosition.x += valuePosition.width+7;
        valuePosition.y += valuePosition.y-86;
        textInputFields[indexCounter].bounds=valuePosition;
        if (typeid(StringNFValue) == typeid(*nfValue)) {
            StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(nfValue);
            ofDrawBitmapString(strNFValue->value.getName(), labelPosition.x, labelPosition.y);
            textInputFields[indexCounter].text = strNFValue->value.get();
            textInputFields[indexCounter].draw();
            
        } else if (typeid(DoubleNFValue) == typeid(*nfValue)) {
            DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(nfValue);
            ofDrawBitmapString(doubleNFValue->value.getName(), labelPosition.x, labelPosition.y);
            textInputFields[indexCounter].text = doubleNFValue->value.get();
            textInputFields[indexCounter].draw();
        } else if (typeid(BoolNFValue) == typeid(*nfValue)) {
            BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(nfValue);
            ofDrawBitmapString(boolNFValue->value.getName(), labelPosition.x, labelPosition.y);
            bool isTrue = boolNFValue->value.get();
            if (isTrue) {
                textInputFields[indexCounter].text = "True";
                textInputFields[indexCounter].draw();
            } else {
                textInputFields[indexCounter].text = "False";
                textInputFields[indexCounter].draw();
            }
        } else if (typeid(IntNFValue) == typeid(*nfValue)) {
            IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(nfValue);
            ofDrawBitmapString(intNFValue->value.getName(), labelPosition.x, labelPosition.y);
            textInputFields[indexCounter].text = intNFValue->value.get();
            textInputFields[indexCounter].draw();
        }
        // set back to the initial position because we are drawing a reference
        textInputFields[indexCounter].bounds = initialPosition;
        indexCounter++;
    }
}

void ofxNodeFlowGUI::draw() { 
    this->drawValue();
}
