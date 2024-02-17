//
//  ofxNodeFlowGUI.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 15.02.24.
//

#ifndef ofxNodeFlowGUI_hpp
#define ofxNodeFlowGUI_hpp

#include "ofMain.h"
// dependencies
#include "GUIParams.hpp"
#include "ofxTextInputField.h"
#include "Button.hpp"

//--------------------------------------------------------------
class NFValue {
public:
    virtual ~NFValue() {}
};

// Example NFValues using ofParameter types
class StringNFValue : public NFValue {
public:
    ofParameter<std::string> value;
    StringNFValue(const std::string& initialValue) : value(initialValue) {}
};

class DoubleNFValue : public NFValue {
public:
    ofParameter<double> value;
    DoubleNFValue(double initialValue) : value(initialValue) {}
};

class BoolNFValue : public NFValue {
public:
    ofParameter<bool> value;
    BoolNFValue(bool initialValue) : value(initialValue) {}
};

class IntNFValue : public NFValue {
public:
    ofParameter<int> value;
    IntNFValue(int initialValue) : value(initialValue) {}
};


//--------------------------------------------------------------
// NFNode class
class NFNode {
private:
    std::vector<NFValue*> nfValues;
    std::vector<NFValue*> drawOrder; // Order of components for drawing
    
public:
    ~NFNode() {
        // Cleanup NFValues
        for (NFValue* nfValue : nfValues) {
            delete nfValue;
        }
    }
    
    template <typename T, typename UIElementType, typename... Args>
    T* addNFValue(const std::string& label, Args&&... args, UIElementType uiElement, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
        // ...

        T* newNFValue = new T(std::forward<Args>(args)...);
        newNFValue->value.setName(label);
        nfValues.push_back(newNFValue);
        drawOrder.push_back(newNFValue);

        // Set up the UIElement
        uiElement.disable();
        uiElement.position.x = x;
        uiElement.position.y = y;
        uiElement.position.height = height;
        uiElement.position.width = width;

        // Convert the value to a string and assign it to uiElement.text
        std::string name, value;
        if (typeid(StringNFValue) == typeid(*newNFValue)) {
            StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(newNFValue);
            name = strNFValue->value.getName();
            value = strNFValue->value.get();
        } else if (typeid(DoubleNFValue) == typeid(*newNFValue)) {
            DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(newNFValue);
            name = doubleNFValue->value.getName();
            value = ofToString(doubleNFValue->value.get());
        } else if (typeid(BoolNFValue) == typeid(*newNFValue)) {
            BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(newNFValue);
            name = boolNFValue->value.getName();
            value = ofToString(boolNFValue->value.get());
        } else if (typeid(IntNFValue) == typeid(*newNFValue)) {
            IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(newNFValue);
            name = intNFValue->value.getName();
            value = ofToString(intNFValue->value.get());
        }
        uiElement.text = value;

        return newNFValue;
    }


    
    // Get the draw order
    const std::vector<NFValue*>& getDrawOrder() const {
        return drawOrder;
    }
    
    
};



class ofxNodeFlowGUI {
public:
    ofxNodeFlowGUI();
    virtual ~ofxNodeFlowGUI();
    // Getter for version as a string
    std::string getVersionString() const {
        return std::to_string(_majorVersion) + "." + std::to_string(_minorVersion) + "." + std::to_string(_patchVersion);
    }
    
    template <typename UIElementType>
    void setup(NFNode& _nfNode, std::vector<UIElementType*>& _uiElements) {
        // Your setup code here
        
        // Load a TrueType font file (replace "your_font.ttf" with the actual filename)
        std::string fontFace = "Roboto-Thin.ttf";
        uint32_t fontSize = 11;
        if (_font.loadFont(fontFace, fontSize)) {
            // Font loaded successfully, you can use it now
            ofLogError() << "ofxNodeFlowGUI::setup(): loaded font" << fontFace+ " size: " << fontSize;
        } else {
            // Handle the case where the font failed to load
            ofLogError() << "ofxNodeFlowGUI::setup(): Failed to load font!";
        }
        // For example, iterate through the vector and do something with each element
        // TODO: implement type specific setters !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for (auto& uiElement : _uiElements) {
            // Perform setup specific to nfUI::UIElement
            // You can use dynamic_cast to check the actual type and perform specific actions
            if (auto* textInputField = dynamic_cast<nfUI::ofxTextInputField*>(uiElement)) {
                // Handle setup for nfUI::ofxTextInputField
                // ...
            } else if (auto* button = dynamic_cast<nfUI::Button*>(uiElement)) {
                // Handle setup for nfUI::Button
                // ...
            }
            // Add other conditions for additional derived types if needed
        }
    }
    
    void update(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements);
    void drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawValue(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements);
    
    void drawStatusBar(const GUIParams& guiParams);
    void drawGrid(const GUIParams& guiParams);
    void draw(NFNode& _nfNode, std::vector<nfUI::UIElement*>& _uiElements);
    nfUI::NfUIConfig _nfuiConfig;
protected:
    ofTrueTypeFont _font;
    int _majorVersion = 0;
    int _minorVersion = 0;
    int _patchVersion = 2;
    
};

#endif /* ofxNodeFlowGUI_hpp */
