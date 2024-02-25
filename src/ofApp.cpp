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
    
    // Set up grid parameters -------------------------------------------------------------------
    _guiParams.setShowGrid(true);
    _guiParams.setGridSize(20);
    _guiParams.setMajorStep(100);
    _guiParams.setMajorGridColor(ofColor(255, 0, 0, 128)); // Red for major grid lines
    _guiParams.setMinorGridColor(ofColor(255, 0, 0, 50));  // Red dark for minor grid lines
    
    // Setup UI Elements -------------------[ DOM configuration / Elements & Styles ]------------
    nfUI::NfUIConfig config;                                            // Create a config object
    float width = 220;
    float margin = 10;
    config.backgroundColor = ofColor(35,38,42);                         // background color of pannel
    config.bounds = ofRectangle(100, 100, width, 20);                   // Set desired position and size
    config.isAbsolutePosition = true;                                   // coordinates are absolute position
    config.setMargin(0);                                               // sets Top, Right, Bottom and Left
    config.setPadding(0);                                               // sets Top, Right, Bottom and Left
    config.contentHeight = 5;                                           // -1 sets to auto (children content height)
    config.contentWidth = width-2*margin;                               // width
    config.isDebug = false;                                             // wether to log debug infos to the console
    _boxxer = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "Pannel",
        "UI Parameters"
    );
   
    config.isAbsolutePosition = false;                                  // relative positioning from now on
    config.backgroundColor = ofColor(56,62,66);                         // background color of label
    config.bounds = ofRectangle(100, 100, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    auto _label = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "GUI CONFIGURATION"
    );
    
    config.backgroundColor = ofColor(30,30,30);
    config.bounds = ofRectangle(100, 100, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 1;
    config.showLabel = true;
    _showGrid = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::BoolNFValue>(
        config,
        "Show Grid",
         _guiParams.getShowGrid()
    );
    

    config.maxTextLength = 4;
    _posX = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "Position X",
        config.bounds.x
    );
    
    _posY = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "Position Y",
        config.bounds.x
    );
    
    _gridSize = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "GridSize",
        _guiParams.getGridSize()
    );
    
    _majorStep = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::IntNFValue>(
        config,
        "MajorStep",
        _guiParams.getMajorStep()
    );
    
    config.maxTextLength = 255;
    _project = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Project",
        "nodeFlowUI"
    );
    
    _version = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Version",
        "v0.0.3"
    );
    
    config.textIsPassword = true;
    _password = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::StringNFValue>(
        config,
        "Password",
        "nodeFlow"
    );
    
    
    config.backgroundColor = ofColor(46, 80, 117);
    config.textIsPassword = true;
    config.marginBottom = 8;  // TODO: this should not be necessary
    myButton = nfUI::createUIElement<nfUI::NfButton, nfUI::StringNFValue>(
        config,
        "Button",
        "Set GUI-Parameters"
    );
    
    ofAddListener(myButton->clicked, this, &ofApp::onButtonSetParametersClicked);
    // The UI rendering tree is specified here
    // boxer is our root element here (which is a Pannel)
    _boxxer->addChild(_label);
    _boxxer->addChild(_posX);
    _boxxer->addChild(_posY);
    _boxxer->addChild(_showGrid);
    _boxxer->addChild(_gridSize);
    _boxxer->addChild(_majorStep);
    _boxxer->addChild(_project);
    _boxxer->addChild(_version);
    _boxxer->addChild(_password);
    _boxxer->addChild(myButton);
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
    // draw UI elements
    if (_boxxer) {
        _boxxer->draw(); // This starts the recursive drawing process
    }
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
            std::cout << "main _showGrid: " << _guiParams._showGrid << "\n";
            break;
        case OF_KEY_F2:
            // F2 key pressed
            _guiParams._showStatusBar = !_guiParams._showStatusBar;
            std::cout << "main _showStatusBar: "  << _guiParams._showStatusBar << "\n";
            break;

        default:
            // Default action for other keys
            cout << "key pressed: " << key << endl;
            break;
    }
}

//--------------------------------------------------------------
// EVENT HANDLERS
//--------------------------------------------------------------
void ofApp::onButtonSetParametersClicked(nfUI::UIEventArgs& eventArgs) {
    // Handle the UI element click event here
    std::cout << "onButtonSetParametersClicked\n";
    // update our GUI parameters from the UI Elements
    _boxxer->setPosition(ofPoint(nfAPI::toInt(_posX->text),nfAPI::toInt(_posY->text)));
    _guiParams.setShowGrid(nfAPI::toBool(_showGrid->text));
    _guiParams.setGridSize(nfAPI::toInt(_gridSize->text));
    _guiParams.setMajorStep(nfAPI::toInt(_majorStep->text));
    _guiParams.setStatusBarText1(_project->text);
    _guiParams.setStatusBarText2(_version->text);

    // _guiParams.setScalingFactor(nfAPI::toDouble(tif7->text));

}

//--------------------------------------------------------------
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
