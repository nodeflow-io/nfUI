#pragma once

#include "ofMain.h"

#include "ofxNodeFlowGUI.hpp"

#include "nfUIElement.hpp"

#include "NfNodeManager.hpp"

#include "NfBoxxer.hpp"
#include "NfPanel.hpp"
#include "NfLabel.hpp"
#include "NfButton.hpp"
#include "NfTextInputField.hpp"
#include "NfDom.hpp"



class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    void drawTxt() ;
    void exit() override;
    
    // your ownn eventhandlers - TODO: reimplement
    void onButtonSetParametersClicked(nfUI::UIEventArgs& eventArgs);
    
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
    
private:
    ofxNodeFlowGUI _nfGUI;
    GUIParams _guiParams;
    
    nfUI::NfNodeManager _nodeManager;
    
    // define UI Elements that require global event handling
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsNode;
    std::shared_ptr<nfUI::NfTextInputField> _posX;
    std::shared_ptr<nfUI::NfTextInputField> _posY;
    std::shared_ptr<nfUI::NfTextInputField> _showGrid;
    std::shared_ptr<nfUI::NfTextInputField> _gridSize;
    std::shared_ptr<nfUI::NfTextInputField> _majorStep;
    std::shared_ptr<nfUI::NfTextInputField> _project;
    std::shared_ptr<nfUI::NfTextInputField> _version;
    std::shared_ptr<nfUI::NfTextInputField> _password;
    std::shared_ptr<nfUI::NfButton> myButton;
    // inspector widget
    std::shared_ptr<nfUI::NfBoxxer> _inspectorNode;
    std::shared_ptr<nfUI::NfBoxxer> _inspectorLabel;
    
};
