//
//  ofxNodeFlowGUI.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 15.02.24.
//

#include "ofxNodeFlowGUI.hpp"

// constructor
ofxNodeFlowGUI::ofxNodeFlowGUI() {
    
}

// destrutor
ofxNodeFlowGUI::~ofxNodeFlowGUI()  {
}


void ofxNodeFlowGUI::setupEventManager(GUIParams& guiParams) {
    // Subscribe to node focus events
    nfUI::NfEventManager::getEventManager().subscribe("gui_hint", [this, &guiParams](const std::string& hintText) {
        guiParams.setStatusBarText3(hintText);
    });
}



void ofxNodeFlowGUI::drawStatusBar(const GUIParams& guiParams) {
    if (!guiParams._showStatusBar) return;
    // Draw the status bar rectangle
    ofSetColor(guiParams._statusBarColor);
    ofDrawRectangle(0, 0, ofGetWidth(), guiParams._statusBarHeight);

    // Draw the text displays
    ofSetColor(guiParams._statusBarTextColor);

    // Draw "nodeFlowUI vx.x.x"
    ofDrawBitmapString(guiParams.getStatusBarText1()+" "+guiParams.getStatusBarText2()+"        "+guiParams.getStatusBarText3(), 10, (guiParams._statusBarHeight / 2)+4);

    // Draw "FPS: XX"
    if(guiParams._showFPS) {
        std::string fpsText = "FPS: " + ofToString(std::round(ofGetFrameRate()));
        ofDrawBitmapString(fpsText, ofGetWidth() - 80, (guiParams._statusBarHeight / 2)+4);
    }
    
}

void ofxNodeFlowGUI::drawGrid(const GUIParams& guiParams) {
    if (!guiParams._showGrid) return;
    // Draw vertical grid lines
    for (int x = 0; x <= ofGetWidth(); x += guiParams._gridSize) {
        if (x % guiParams._majorStep == 0) {
            ofSetColor(guiParams._majorGridColor);
            ofDrawLine(x, 0, x, ofGetHeight());

            // Draw text label
            ofDrawBitmapString(ofToString(x), x, ofGetHeight() - 5);
        } else {
            ofSetColor(guiParams._minorGridColor);
            ofDrawLine(x, 0, x, ofGetHeight());
        }
    }

    // Draw horizontal grid lines
    for (int y = 0; y <= ofGetHeight(); y += guiParams._gridSize) {
        if (y % guiParams._majorStep == 0) {
            ofSetColor(guiParams._majorGridColor);
            ofDrawLine(0, y, ofGetWidth(), y);

            // Draw text label
            ofDrawBitmapString(ofToString(y), 5, y);
        } else {
            ofSetColor(guiParams._minorGridColor);
            ofDrawLine(0, y, ofGetWidth(), y);
        }
    }
}
