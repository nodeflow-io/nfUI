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
#include "ofxTextInputField.h"

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
    T* addNFValue(const std::string& label, Args&&... args, UIElementType& uiElement, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
        // ...
        
        T* newNFValue = new T(std::forward<Args>(args)...);
        newNFValue->value.setName(label); // Set the label for the parameter
        nfValues.push_back(newNFValue);
        drawOrder.push_back(newNFValue); // Add to draw order
        
        // Set up the UIElement
        uiElement.disable();
        uiElement.position.x = x;
        uiElement.position.y = y;
        uiElement.position.height = height;
        uiElement.position.width = width;
        
        // Convert the value to a string and assign it to uiElement.text
        std::string name, value;
        // get name and value as strings for display
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
        // uiElement.setFont(font); // we just render the default bitmap font
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
    
    void setup(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void update(NFNode& nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawValue(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void draw(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    nfUI::NfUIConfig _nfuiConfig;
protected:
    ofTrueTypeFont _font;
    
};

#endif /* ofxNodeFlowGUI_hpp */
