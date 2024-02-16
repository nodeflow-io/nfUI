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

    // Add an NFValue to the node with label, value, and textInputField
    template <typename T, typename... Args>
    T* addNFValue(const std::string& label, Args&&... args, nfUI::ofxTextInputField& textInputField, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
        T* newNFValue = new T(std::forward<Args>(args)...);
        newNFValue->value.setName(label); // Set the label for the parameter
        nfValues.push_back(newNFValue);
        drawOrder.push_back(newNFValue); // Add to draw order
        
        // Set up the textInputField
        textInputField.disable();
        textInputField.position.x = x;
        textInputField.position.y = y;
        textInputField.position.height = height;
        textInputField.position.width = width;
        // textInputField.setFont(font); // we just render the default bitmap font
        

        return newNFValue;
    }

    // Get an NFValue of a specific type
    template <typename T>
    T* getNFValue() const {
        for (NFValue* nfValue : nfValues) {
            if (typeid(T) == typeid(*nfValue)) {
                return dynamic_cast<T*>(nfValue);
            }
        }
        return nullptr;
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
    
    void setup();
    void drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawValue();
    void draw();
protected:
    ofTrueTypeFont font;
    std::vector<nfUI::ofxTextInputField> textInputFields;
    NFNode nfNode;
};

#endif /* ofxNodeFlowGUI_hpp */
