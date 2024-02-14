#pragma once

#include "ofMain.h"
#include "ofxTextInputField.h"



// NFValue class
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

// NFNode class (formerly Node)
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
    // Add an NFValue to the node with label, value, and textInputField
    template <typename T, typename... Args>
    T* addNFValue(const std::string& label, Args&&... args, ofxTextInputField& textInputField, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
        T* newNFValue = new T(std::forward<Args>(args)...);
        newNFValue->value.setName(label); // Set the label for the parameter
        nfValues.push_back(newNFValue);
        drawOrder.push_back(newNFValue); // Add to draw order
        
        textInputField.setup();
        textInputField.text = ofToString(newNFValue->value.get());
        textInputField.bounds.x = x;
        textInputField.bounds.y = y;
        textInputField.bounds.height = height;
        textInputField.bounds.width = width;
        textInputField.setFont(font);
        // Set up the textInputField

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


template <typename ParameterType>
class ParameterDisplay {
public:
    ParameterDisplay(ofParameter<ParameterType>& parameter, float x, float y, float width, float height)
        : parameter(parameter), x(x), y(y), width(width), height(height) {}

    void draw() {
        ofDrawBitmapString(ofToString(parameter.get()), x, y); // Use ofToString to handle different types
        ofNoFill();
        ofDrawRectangle(x, y, width, height);
        ofFill();
    }

private:
    ofParameter<ParameterType>& parameter;
    float x;
    float y;
    float width;
    float height;
};

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
        void drawValue();
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
        ofTrueTypeFont font;
        // ofxTextInputField monoLineTextInput, multilineTextInput;
private:
    //
    // ofParameter<std::string> myParameter;
    // ParameterDisplay<std::string>* parameterDisplay;
    
    // NF
    std::vector<ofxTextInputField> textInputFields;
    NFNode nfNode;
		
};
