#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    ofTrueTypeFont font;
    font.load(OF_TTF_SERIF, 18);
    
    
    // ---
    nfUI::ofxTextInputField textInputField1;
    nfUI::ofxTextInputField textInputField2;
    nfUI::ofxTextInputField textInputField3;
    nfUI::ofxTextInputField textInputField4;
    nfUI::ofxTextInputField textInputField5;
    
    _textInputFields.push_back(textInputField1);
    _textInputFields.push_back(textInputField2);
    _textInputFields.push_back(textInputField3);
    _textInputFields.push_back(textInputField4);
    _textInputFields.push_back(textInputField5);
    
    // Add NFValues to the node with labels and set up textInputFields
    _nfNode.addNFValue<DoubleNFValue, double>("Stepper", 3.14, _textInputFields[0], 20, 20, 120, 20, _font);
    _nfNode.addNFValue<IntNFValue, int>("Accelleration", 42, _textInputFields[1], 20, 40, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, bool>("Reset", false, _textInputFields[2], 20, 60, 120, 20, _font);
    _nfNode.addNFValue<StringNFValue, std::string>("Mode", "Forward", _textInputFields[3], 20, 80, 120, 20, _font);
    _nfNode.addNFValue<BoolNFValue, bool>("isReady", true, _textInputFields[4], 20, 100, 120, 20, _font);
    // --
    _nfGUI.setup(_nfNode, _textInputFields);
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    _nfGUI.draw(this->_nfNode, this->_textInputFields);
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
