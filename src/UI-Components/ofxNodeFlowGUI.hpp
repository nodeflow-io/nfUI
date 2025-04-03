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
#include "NfEventManager.hpp"



class ofxNodeFlowGUI {
public:
    ofxNodeFlowGUI();
    virtual ~ofxNodeFlowGUI();
    void setupEventManager(GUIParams& guiParams);
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
    int _patchVersion = 7;
    
};

#endif /* ofxNodeFlowGUI_hpp */
