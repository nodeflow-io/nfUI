#pragma once

#include "ofMain.h"

#include "ofxNodeFlowGUI.hpp"

#include "nfUIElement.hpp"

#include "NfNodeManager.hpp"

#include "NfBoxxer.hpp"
#include "NfPanel.hpp"
#include "NfLabel.hpp"
#include "NfToggleSwitch.hpp"
#include "NfButton.hpp"
#include "NfTextInputField.hpp"
#include "NfDom.hpp"
#include "GUIParams.hpp"



class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    void drawTxt() ;
    void exit() override;
    
    // your ownn eventhandlers
    void onGuiParametersButtonClicked(nfUI::UIEventArgs& eventArgs);
    void onGuiParametersShowGridClicked(nfUI::UIEventArgs& eventArgs);
    void onGuiParametersShowStatusBarClicked(nfUI::UIEventArgs& eventArgs);
    void onGuiParametersShowStatusFPSClicked(nfUI::UIEventArgs& eventArgs);
    void onInspectorButtonClicked(nfUI::UIEventArgs& eventArgs);
    
    // default of eventhandlers
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
    
    GUIParams _guiParams;
    ofxNodeFlowGUI _nfGUI;
    
    // nfUI::NfNodeManager _nodeManager;
    
    // define UI Elements that may require global event handling
    // Gui Parameters widget
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsNode;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsLabel;
    std::shared_ptr<nfUI::NfToggleSwitch> _guiParamsShowGrid;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsGridSize;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsMajorStep;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsProject;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsVersion;
    std::shared_ptr<nfUI::NfBoxxer> _guiParamsPassword;
    std::shared_ptr<nfUI::NfToggleSwitch> _guiParamsShowStatusBar;
    std::shared_ptr<nfUI::NfToggleSwitch> _guiParamsShowStatusFPS;
    std::shared_ptr<nfUI::NfButton> _guiParamsButton;
    // Inspector widget
    std::shared_ptr<nfUI::NfBoxxer> _inspectorNode;
    std::shared_ptr<nfUI::NfBoxxer> _inspectorLabel;
    std::shared_ptr<nfUI::NfBoxxer> _inspectorPosX;
    std::shared_ptr<nfUI::NfBoxxer> _inspectorPosY;
    std::shared_ptr<nfUI::NfButton> _inspectorButton;
    
};
