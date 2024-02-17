//
//  ofxNodeFlowGUI.cpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 15.02.24.
//

#include "ofxNodeFlowGUI.hpp"
#include "UIElement.hpp"

// constructor
ofxNodeFlowGUI::ofxNodeFlowGUI() {
}

// destrutor
ofxNodeFlowGUI::~ofxNodeFlowGUI()  {
}


void ofxNodeFlowGUI::update(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements) {
    
}

void ofxNodeFlowGUI::drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    // Set color to backgroundcolor000 (filled)
    ofSetColor(_nfuiConfig.backgroundColor);
    // Draw a filled rectangle at position (100, 100) with a width of 200 and height of 150
    ofDrawRectangle(x, y, width, height);
    // Set color to black (outline)
    ofSetColor(_nfuiConfig.borderColor);
    // Draw the same rectangle with no fill to create the outline
    ofNoFill();
    ofDrawRectangle(x, y, width, height);
    ofDrawRectangle(x + width, y, width, height);
    ofFill(); // Restore fill mode for subsequent drawings
}


void ofxNodeFlowGUI::drawValue(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements) {
    ofBackground(0);
    ofSetColor(_nfuiConfig.textColor);
    ofPushStyle();
    uint32_t py = 20;
    uint32_t x = 20;
    uint32_t y = 20;
    uint32_t channelSpacing = _nfuiConfig.height;
    uint32_t paddingHorizontal = _nfuiConfig.padding;

    // Access and modify NFValues in the order they were added
    const std::vector<NFValue*>& drawOrder = _nfNode.getDrawOrder();
    size_t indexCounter = 0;
    std::string name;
    std::string value;

    // iterate over all name / value pairs
    for (const auto& nfValue : drawOrder) {
        ofRectangle initialPosition = _uiElements[indexCounter]->getBounds();
        ofRectangle labelPosition = initialPosition;
        ofRectangle valuePosition = initialPosition;

        this->drawPanel(labelPosition.x, labelPosition.y, labelPosition.width, _nfuiConfig.height);
        ofSetColor(_nfuiConfig.textColor);

        // adjust label position for font rendering
        y = py + (indexCounter * channelSpacing);
        labelPosition.x = x + paddingHorizontal;
        labelPosition.y = y + 14;
        valuePosition.x = x + valuePosition.width + 7;
        valuePosition.y = y;

        // get name and value as strings for display
        if (typeid(StringNFValue) == typeid(*nfValue)) {
            StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(nfValue);
            name = strNFValue->value.getName();
            value = strNFValue->value.get();
        } else if (typeid(DoubleNFValue) == typeid(*nfValue)) {
            DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(nfValue);
            name = doubleNFValue->value.getName();
            value = ofToString(doubleNFValue->value.get());
        } else if (typeid(BoolNFValue) == typeid(*nfValue)) {
            BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(nfValue);
            name = boolNFValue->value.getName();
            value = ofToString(boolNFValue->value.get());
        } else if (typeid(IntNFValue) == typeid(*nfValue)) {
            IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(nfValue);
            name = intNFValue->value.getName();
            value = ofToString(intNFValue->value.get());
        }

        // draw input field
        glPushMatrix();
        ofDrawBitmapString(name, labelPosition.x, labelPosition.y);
        glTranslatef(0, -2, 0);
        _uiElements[indexCounter]->setup();
        _uiElements[indexCounter]->setBounds(valuePosition);
        _uiElements[indexCounter]->draw();
        glPopMatrix();

        indexCounter++;
    }

    ofPopStyle();
}

void ofxNodeFlowGUI::draw(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements) {
    this->drawValue(_nfNode, _uiElements);
}
