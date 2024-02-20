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
    ofTrueTypeFont font;
    font.load(OF_TTF_SERIF, 18);
    
    // --- setup debug grid configuration
    // Set up status bar parameters -------------------------------------------------------------
    _guiParams.setShowStatusBar(true);
    _guiParams.setStatusBarHeight(20);
    _guiParams.setStatusBarColor(ofColor(100, 100, 100, 255));
    _guiParams.setStatusBarTextColor(ofColor(255, 255, 0, 255));
    
    // Set up grid parameters -------------------------------------------------------------------
    _guiParams.setShowGrid(false);
    _guiParams.setGridSize(20);
    _guiParams.setMajorStep(100);
    _guiParams.setMinorStep(20);
    _guiParams.setMajorGridColor(ofColor(255, 0, 0, 128)); // Red for major grid lines
    _guiParams.setMinorGridColor(ofColor(255, 0, 0, 50));  // Red dark for minor grid lines
    
    // Setup UI Elements -------------------[ DOM configuration / Elements & Styles ]------------
    nfUI::NfUIConfig config;                // Set your configuration parameters here
    auto configShowGrid = config;           // make a copy of default config
    configShowGrid.maxTextLength=1;         // set maxTextLength to 1 (it is a Bool 0/1)
    
    // define textfields
    tif1 = new nfUI::ofxTextInputField(configShowGrid, "Show Grid");
    
    auto configGridSize = config;           // make a copy of default config
    configGridSize.maxTextLength=4;         // set maxTextLength to 4
                                            // we use the same config for all three integer fields
    tif2 = new nfUI::ofxTextInputField(configGridSize, "Grid Size");
    tif3 = new nfUI::ofxTextInputField(configGridSize, "Major Step");
    tif4 = new nfUI::ofxTextInputField(configGridSize, "Minor Step");
    auto configStatusText = config;         // make a copy of default config
    tif5 = new nfUI::ofxTextInputField(configStatusText, "StatusText");
    auto configPassword = configStatusText;
    configPassword.textIsPassword = true;   // make the text input a password (*****)
    tif6 = new nfUI::ofxTextInputField(configPassword, "Password");
    tif7 = new nfUI::ofxTextInputField(configGridSize, "Scaling");
    // define button
    nfUI::Button* buttonSetParameters = new nfUI::Button(config, "Set Params");
    
    // setup event handlers for the callbacks
    ofAddListener(buttonSetParameters->clicked, this, &ofApp::onButtonSetParametersClicked);
    
    // add every UIElement to our UIElements --[ Rendering order ]-------------------------------
    _uiElements.emplace_back(tif1);
    _uiElements.emplace_back(tif2);
    _uiElements.emplace_back(tif3);
    _uiElements.emplace_back(tif4);
    _uiElements.emplace_back(tif5);
    _uiElements.emplace_back(tif6);
    _uiElements.emplace_back(tif7);
    _uiElements.emplace_back(buttonSetParameters);
    
    // Add NFValues to the node with labels and set up UIElements
    // label, value, *UIElelemnt, initial bounds
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>(tif1->parameters.getName(), _guiParams.getShowGrid(), *tif1, 20, 60, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif2->parameters.getName(), _guiParams.getGridSize(), *tif2, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif3->parameters.getName(), _guiParams.getMajorStep(), *tif3, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif4->parameters.getName(), _guiParams.getMinorStep(), *tif4, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::ofxTextInputField, std::string>("Project", "nodeFlowUI", *tif5, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::ofxTextInputField, std::string>("Password", "nodeFlowUI", *tif6, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<DoubleNFValue, nfUI::ofxTextInputField, double>("Scaling", _guiParams.getScalingFactor(), *tif7, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::Button, std::string>("Button", buttonSetParameters->parameters.getName(), *buttonSetParameters, 20, 80, 100, 20, _font);

    // setup GUI
    _nfGUI.setup(_nfNode, _uiElements);
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    // draw the background grid
    _nfGUI.drawGrid(this->_guiParams);
    // draw status bar
    _nfGUI.drawStatusBar(this->_guiParams);
    // draw UI elements
    _nfGUI.draw(this->_nfNode, this->_uiElements);
    ofSetColor(0);
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
            cout << "Key pressed: " << key << endl;
            break;
    }
}

//--------------------------------------------------------------
// EVENT HANDLERS
//--------------------------------------------------------------
void ofApp::onButtonSetParametersClicked(nfUI::UIEventArgs& eventArgs) {
    // Handle the UI element click event here
    std::cout << "onButtonSetParametersClicked\n";
    _guiParams._showGrid = nfAPI::toBool(tif1->text);
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
