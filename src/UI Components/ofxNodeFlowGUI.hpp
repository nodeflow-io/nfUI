//
//  ofxNodeFlowGUI.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 15.02.24.
//

#ifndef ofxNodeFlowGUI_hpp
#define ofxNodeFlowGUI_hpp

#include "ofMain.h"
// dependencies to UI
#include "GUIParams.hpp"


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






class ofxNodeFlowGUI {
public:
    ofxNodeFlowGUI();
    virtual ~ofxNodeFlowGUI();
    // Getter for version as a string
    std::string getVersionString() const {
        return std::to_string(_majorVersion) + "." + std::to_string(_minorVersion) + "." + std::to_string(_patchVersion);
    }

    void drawStatusBar(const GUIParams& guiParams);
    void drawGrid(const GUIParams& guiParams);

protected:
    ofTrueTypeFont _font;
    int _majorVersion = 0;
    int _minorVersion = 0;
    int _patchVersion = 3;
    
};

#endif /* ofxNodeFlowGUI_hpp */
