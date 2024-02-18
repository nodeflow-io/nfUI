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
    // Set up status bar parameters
    _guiParams.setShowStatusBar(true);
    _guiParams.setStatusBarHeight(20);
    _guiParams.setStatusBarColor(ofColor(100, 100, 100, 255));
    _guiParams.setStatusBarTextColor(ofColor(255, 255, 0, 255));
    // Set up grid parameters
    _guiParams.setShowGrid(false);
    _guiParams.setGridSize(20);
    _guiParams.setMajorStep(100);
    _guiParams.setMinorStep(20);
    _guiParams.setMajorGridColor(ofColor(255, 0, 0, 128)); // Red for major grid lines
    _guiParams.setMinorGridColor(ofColor(255, 0, 0, 50));  // Red dark for minor grid lines
    
    // --- setup entities
    nfUI::NfUIConfig config; // Set your configuration parameters here
    nfUI::ofxTextInputField* tif1 = new nfUI::ofxTextInputField(config, "Show Grid");
    nfUI::ofxTextInputField* tif2 = new nfUI::ofxTextInputField(config, "Grid Size");
    nfUI::ofxTextInputField* tif3 = new nfUI::ofxTextInputField(config, "Major Step");
    nfUI::ofxTextInputField* tif4 = new nfUI::ofxTextInputField(config, "Minor Step");

    // nfUI::ofxTextInputField* textInputField4 = new nfUI::ofxTextInputField();
    // nfUI::ofxTextInputField* textInputField5 = new nfUI::ofxTextInputField();
    nfUI::Button* buttonSetParameters = new nfUI::Button(config, "Set Parameters");
    
    // setup event handlers for the callbacks
    ofAddListener(buttonSetParameters->clicked, this, &ofApp::onButtonSetParametersClicked);
    
    // add every UIElement to our UIElements structure
    _uiElements.emplace_back(tif1);
    _uiElements.emplace_back(tif2);
    _uiElements.emplace_back(tif3);
    _uiElements.emplace_back(tif4);
    // _uiElements.emplace_back(textInputField4);
    // _uiElements.emplace_back(textInputField5);
    _uiElements.emplace_back(buttonSetParameters);
    
    // Add NFValues to the node with labels and set up UIElements
    // label, value
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>(tif1->parameters.getName(), _guiParams.getShowGrid(), *tif1, 20, 60, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif2->parameters.getName(), _guiParams.getGridSize(), *tif2, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif3->parameters.getName(), _guiParams.getMajorStep(), *tif3, 20, 40, 100, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>(tif4->parameters.getName(), _guiParams.getMajorStep(), *tif4, 20, 40, 100, 20, _font);
    
    _nfNode.addNFValue<StringNFValue, nfUI::Button, std::string>("Button", buttonSetParameters->parameters.getName(), *buttonSetParameters, 20, 80, 100, 20, _font);


   /*
    _nfNode.addNFValue<DoubleNFValue, nfUI::ofxTextInputField, double>("Stepper", 3.14, *textInputField1, 20, 20, 120, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>("Acceleration", 42, *textInputField2, 20, 40, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>("Reset", false, *textInputField3, 20, 60, 120, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::ofxTextInputField, std::string>("Mode", "Forward", *textInputField4, 20, 80, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>("isReady", true, *textInputField5, 20, 100, 120, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::Button, std::string>("Button", "Solve Production", *buttonCalculate, 20, 80, 120, 20, _font);
    */
    
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
        case OF_KEY_RETURN: // ENTER key
            // Action for ENTER key
            // put it on std::out
            // Iterate over NFNode's draw order
                for (const auto& nfValue : _nfNode.getDrawOrder()) {
                    // Iterate over _textInputFields to find the corresponding one
                    for (const auto& textField : _textInputFields) {
                        // Assuming the textInputFields are associated with NFValues based on their positions in the vector
                        // You may need a more sophisticated way to associate NFValues with textInputFields in your actual code
                        if (&textField == &_textInputFields[std::distance(&_nfNode.getDrawOrder()[0], &nfValue)]) {
                            // Access name and value
                            std::string name, value;
                            if (typeid(StringNFValue) == typeid(*nfValue)) {
                                StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(nfValue);
                                name = strNFValue->value.getName();
                                value = strNFValue->value.get();
                            } else if (typeid(DoubleNFValue) == typeid(*nfValue)) {
                                DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(nfValue);
                                name = doubleNFValue->value.getName();
                                value = ofToString(doubleNFValue->value.get());
                            } else if (typeid(BoolNFValue) == typeid(*nfValue)) {
                                BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(nfValue);
                                name = boolNFValue->value.getName();
                                value = ofToString(boolNFValue->value.get());
                            } else if (typeid(IntNFValue) == typeid(*nfValue)) {
                                IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(nfValue);
                                name = intNFValue->value.getName();
                                value = ofToString(intNFValue->value.get());
                            }

                            // Draw the name and value using ofDrawBitmapString or any other rendering method
                            ofDrawBitmapString(name + ": " + value, 150, 20);
                            // Additional drawing logic for textInputFields can be added here
                            std::cout << textField.text << std::endl;
                        }
                    }
                }
            break;
            
        case 'g': // 'g' key
            // Action for 'g' key
            _guiParams._showGrid = !_guiParams._showGrid;
            std::cout << "main _showGrid: " << _guiParams._showGrid << "\n";
            break;
            
        case 'h': // 'h' key
            // Action for 'h' key
            break;
        
        case 'i': // 'g' key
            // Action for 'g' key
            _guiParams._showStatusBar = !_guiParams._showStatusBar;
            std::cout << "main _showStatusBar: "  << _guiParams._showStatusBar << "\n";
            break;

        case '1': // '1' key
            // Action for '1' key
            break;

        case '2': // '2' key
            // Action for '2' key
            break;

        case '3': // '3' key
            // Action for '3' key
            break;

        case '4': // '4' key
            // Action for '4' key
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
