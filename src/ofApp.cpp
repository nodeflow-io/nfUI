#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    ofTrueTypeFont font;
    font.load(OF_TTF_SERIF, 18);
    
    // --- setup entities
    nfUI::ofxTextInputField* textInputField1 = new nfUI::ofxTextInputField();
    nfUI::ofxTextInputField* textInputField2 = new nfUI::ofxTextInputField();
    nfUI::ofxTextInputField* textInputField3 = new nfUI::ofxTextInputField();
    nfUI::ofxTextInputField* textInputField4 = new nfUI::ofxTextInputField();
    nfUI::ofxTextInputField* textInputField5 = new nfUI::ofxTextInputField();
    nfUI::Button* buttonCalculate = new nfUI::Button();
    
    textInputField1->setup();
    _uiElements.push_back(textInputField1);
    _uiElements.push_back(textInputField2);
    _uiElements.push_back(textInputField3);
    _uiElements.push_back(textInputField4);
    _uiElements.push_back(textInputField5);
    _uiElements.push_back(buttonCalculate);
    
    // Add NFValues to the node with labels and set up UIElements
    _nfNode.addNFValue<DoubleNFValue, nfUI::ofxTextInputField, double>("Stepper", 3.14, *textInputField1, 20, 20, 120, 20, _font);
    _nfNode.addNFValue<IntNFValue, nfUI::ofxTextInputField, int>("Acceleration", 42, *textInputField2, 20, 40, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>("Reset", false, *textInputField3, 20, 60, 120, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::ofxTextInputField, std::string>("Mode", "Forward", *textInputField4, 20, 80, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, nfUI::ofxTextInputField, bool>("isReady", true, *textInputField5, 20, 100, 120, 20, _font);
    _nfNode.addNFValue<StringNFValue, nfUI::Button, std::string>("Button", "Solve Production", *buttonCalculate, 20, 80, 120, 20, _font);

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

        case 'h': // 'h' key
            // Action for 'h' key
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
