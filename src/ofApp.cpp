#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    // set the logging level you can use:
    // OF_LOG_VERBOSE
    // OF_LOG_NOTICE
    // OF_LOG_WARNING
    // OF_LOG_ERROR
    // OF_LOG_FATAL_ERROR
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    // --- setup debug grid configuration
    // Set up status bar parameters -------------------------------------------------------------
    _guiParams.setShowStatusBar(true);
    _guiParams.setStatusBarHeight(20);
    _guiParams.setStatusBarColor(ofColor(35,38,42));
    _guiParams.setStatusBarTextColor(ofColor(41, 225, 255, 255));
    _guiParams.setStatusBarText1("nodeFlowUI");
    _guiParams.setStatusBarText2(_nfGUI.getVersionString());
    _guiParams.setStatusBarText3("Click on a node to see details here");
    _guiParams.setShowFPS(false);
    
    // Set up grid parameters -------------------------------------------------------------------
    _guiParams.setShowGrid(true);
    _guiParams.setGridSize(20);
    _guiParams.setMajorStep(100);
    _guiParams.setMajorGridColor(ofColor(255, 0, 0, 128)); // Red for major grid lines
    _guiParams.setMinorGridColor(ofColor(255, 0, 0, 50));  // Red dark for minor grid lines
    
    // Set up gui event handlers ----------------------------------------------------------------
    _nfGUI.setupEventManager(_guiParams);
    
    // Setup UI Elements -------------------[ DOM configuration / Elements & Styles ]------------
    nfUI::NfUIConfig config;                                            // Create a config object
    float width = 220;
    float margin = 10;
    float posX = 300;
    float posY = 100;
    config.backgroundColor = ofColor(20,25,31);                         // background color of pannel
    config.focusBackgroundColor = ofColor(35,38,42);                    // focus color of panel
    config.focusColor = ofColor::black;
    config.bounds = ofRectangle(posX, posY, width, 20);                 // Set desired position and size
    config.isAbsolutePosition = true;                                   // coordinates are absolute position
    config.setMargin(0);                                                // sets Top, Right, Bottom and Left
    config.setPadding(0);                                               // sets Top, Right, Bottom and Left
    config.contentHeight = 5;                                           // -1 sets to auto (children content height)
    config.contentWidth = width-2*margin;                               // width
    config.isDebug = false;                                             // wether to log debug infos to the console
    _guiParamsNode = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "GUI Configuration",
        "GUI Parameters"
    );
   
    config.isAbsolutePosition = false;                                  // relative positioning from now on
    config.backgroundColor = ofColor(56, 62, 66, 128);                  // background color of label
    config.focusBackgroundColor = ofColor(56, 62, 66, 255);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    _guiParamsLabel = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "GUI CONFIGURATION"
    );
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 1;
    config.showLabel = true;
    _guiParamsShowGrid = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::BoolNFValue>(
        config,
        "Show Grid",
         _guiParams.getShowGrid()
    );
    

    config.maxTextLength = 4;
    _guiParamsGridSize = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "GridSize",
        _guiParams.getGridSize()
    );
    
    _guiParamsMajorStep = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "MajorStep",
        _guiParams.getMajorStep()
    );
    
    config.maxTextLength = 255;
    _guiParamsProject = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Project",
        "nodeFlowUI"
    );
    
    _guiParamsVersion = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Version",
        "v"+_nfGUI.getVersionString()
    );
    
    config.textIsPassword = true;
    _guiParamsPassword = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Password",
        "nodeFlow"
    );
    
    
    config.backgroundColor = ofColor(46, 80, 117);
    config.focusBackgroundColor = ofColor::yellow;
    config.focusColor = ofColor::black;
    config.textIsPassword = true;
    config.marginBottom = 8;  // TODO: this should not be necessary
    _guiParamsButton = nfUI::createUIElement<nfUI::NfButton, nfUI::StringNFValue>(
        config,
        "Button",
        "Set GUI-Parameters"
    );

    // Setup Inspector Widget -----------------[ DOM configuration / Elements & Styles ]------------
    width+=40;                                                          // the inspector needs more room
    posX = 0;
    posY = 20;
    config.backgroundColor = ofColor(20,25,31);                         // background color of pannel
    config.focusBackgroundColor = ofColor(35,38,42);                    // focus color of panel
    config.bounds = ofRectangle(posX, posY, width, 20);                 // Set desired position and size
    config.isAbsolutePosition = true;                                   // coordinates are absolute position
    config.setMargin(0);                                                // sets Top, Right, Bottom and Left
    config.setPadding(0);                                               // sets Top, Right, Bottom and Left
    config.contentHeight = 5;                                           // -1 sets to auto (children content height)
    config.contentWidth = width-2*margin;                               // width
    config.textIsPassword = false;
    config.isDebug = false;                                             // wether to log debug infos to the console
    _inspectorNode = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "Inspector",
        "Inspector"
    );
    
    config.isAbsolutePosition = false;                                  // relative positioning from now on
    config.backgroundColor = ofColor(56, 62, 66, 128);                  // background color of label
    config.focusBackgroundColor = ofColor(56,62,66, 255);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    auto _inspectorLabel = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "INSPECTOR (Gui Configuration)"
    );
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 4;
    config.showLabel = true;
    
    
    _inspectorPosX = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "Position X",
        300
    );
    
    _inspectorPosY = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "Position Y",
        100
    );
    
    config.backgroundColor = ofColor(46, 80, 117);
    config.focusBackgroundColor = ofColor::yellow;
    config.focusColor = ofColor::black;
    config.textIsPassword = true;
    config.marginBottom = 8;  // TODO: this should not be necessary
    _inspectorButton = nfUI::createUIElement<nfUI::NfButton, nfUI::StringNFValue>(
        config,
        "Button",
        "Update Widget"
    );
    
    // The UI rendering tree is specified here
    // adding childs to GUI-Parameters widget here
    _guiParamsNode->addChild(_guiParamsLabel);
    _guiParamsNode->addChild(_guiParamsShowGrid);
    _guiParamsNode->addChild(_guiParamsGridSize);
    _guiParamsNode->addChild(_guiParamsMajorStep);
    _guiParamsNode->addChild(_guiParamsProject);
    _guiParamsNode->addChild(_guiParamsVersion);
    _guiParamsNode->addChild(_guiParamsPassword);
    _guiParamsNode->addChild(_guiParamsButton);
    // add event handlers for interactive element
     ofAddListener(_guiParamsButton->clicked, this, &ofApp::onGuiParametersButtonClicked);
    
    // adding childs to inspector widget here
    _inspectorNode->addChild(_inspectorLabel);
    _inspectorNode->addChild(_inspectorPosX);
    _inspectorNode->addChild(_inspectorPosY);
    _inspectorNode->addChild(_inspectorButton);
    // add event handlers for interactive element
     ofAddListener(_inspectorButton->clicked, this, &ofApp::onInspectorButtonClicked);
    
    // adding widgets to NodeManager
    _nodeManager.addNode(_guiParamsNode); // Add the GUI Parameters to the node manager
    _nodeManager.addNode(_inspectorNode); // Add the inspector to the node manager
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofPushMatrix(); // Save the current transformation matrix
    _nfGUI.drawGrid(this->_guiParams);
    // draw status bar
    _nfGUI.drawStatusBar(this->_guiParams);
    
    // draw nodes
    _nodeManager.drawNodes(); // This starts the recursive drawing process
    
    ofPopMatrix(); // Restore the transformation matrix
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Perform actions based on the pressed key
    switch (key) {
        case OF_KEY_F1:
            // F1 key pressed
            _guiParams._showGrid = !_guiParams._showGrid;
            std::cout << "ofApp::keyPressed _showGrid: " << _guiParams._showGrid << "\n";
            break;
        case OF_KEY_F2:
            // F2 key pressed
            _guiParams._showStatusBar = !_guiParams._showStatusBar;
            std::cout << "ofApp::keyPressed _showStatusBar: "  << _guiParams._showStatusBar << "\n";
            break;
        case OF_KEY_F3:
            // F3 key pressed
            _guiParams.setShowFPS(!_guiParams.getShowFPS());
            std::cout << "ofApp::keyPressed _showFPS: "  << _guiParams._showFPS << "\n";
            break;

        default:
            // Default action for other keys
            cout << "ofApp::keyPressed: " << key << endl;
            break;
    }
}

//--------------------------------------------------------------
// YOUR OWN EVENT HANDLERS
//----------------------------------------[ Buttons ]-----------

void ofApp::onGuiParametersButtonClicked(nfUI::UIEventArgs& eventArgs) {
    std::cout << "ofApp::onGuiParametersButtonClicked\n";
    // update our GUI parameters from the UI Elements
    _guiParams.setShowGrid(nfAPI::toBool(_guiParamsShowGrid->text));
    _guiParams.setGridSize(nfAPI::toInt(_guiParamsGridSize->text));
    _guiParams.setMajorStep(nfAPI::toInt(_guiParamsMajorStep->text));
    _guiParams.setStatusBarText1(_guiParamsProject->text);
    _guiParams.setStatusBarText2(_guiParamsVersion->text);
}

void ofApp::onInspectorButtonClicked(nfUI::UIEventArgs& eventArgs) {
    std::cout << "ofApp::onInspectorButtonClicked\n";
    // update the position oof the GUI parameters node from the inspector widget
    _guiParamsNode->setPosition(ofPoint(nfAPI::toInt(_inspectorPosX->text),nfAPI::toInt(_inspectorPosY->text)));

}

//--------------------------------------------------------------
// DEFAULT OPEN FRAMEWORKS EVENT HANDLERS
//----------------------------------------[ Buttons ]-----------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
