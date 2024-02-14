#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    ofTrueTypeFont font;
    font.load("/System/Library/Fonts/Supplemental/Times New Roman.ttf", 18);
    /*
    monoLineTextInput.setup();
    monoLineTextInput.text = "hello world";
    monoLineTextInput.bounds.x = 100;
    monoLineTextInput.bounds.y = 100;
    monoLineTextInput.bounds.height = 40;
    monoLineTextInput.bounds.width = 188;
    multilineTextInput.setup();
    
    multilineTextInput.text = "0: #include \"testApp.h\"\n"
    "1: \n"
    "2: //--------------------------------------------------------------\n"
    "3: void testApp::setup() {\n"
    "4: \n"
    "5:     monoLineTextInput.setup();\n"
    "6:     monoLineTextInput.text = \"hello world\";\n"
    "7:     monoLineTextInput.bounds.x = 100;\n"
    "8:     monoLineTextInput.bounds.y = 100;\n"
    "9:\n"
    "10:    multilineTextInput.setup();\n"
    "11: \n"
    "12:     monoLineTextInput.text = \"hello world\";\n"
    "13:    monoLineTextInput.bounds.x = 100;\n"
    "14:    monoLineTextInput.bounds.y = 100;\n"
    "15:\n"
    "16:\n"
    "17: }\n";
    multilineTextInput.bounds.x = 300;
    multilineTextInput.bounds.y = 100;
    multilineTextInput.bounds.width = 400;
    multilineTextInput.bounds.height = 500;
    multilineTextInput.multiline = true;
    fontdemo.loadFont(OF_TTF_SERIF, 18);
    monoLineTextInput.setFont(fontdemo);
     
    
    myParameter.set("My Parameter", "testingclass");
    
    // Initialize ParameterDisplay with x, y, width, height
    parameterDisplay = new ParameterDisplay(myParameter, 100, 400, 188, 40);
     */
    // Add NFValues to the node with labels
    ofxTextInputField textInputField1;
    ofxTextInputField textInputField2;
    ofxTextInputField textInputField3;
    ofxTextInputField textInputField4;
    ofxTextInputField textInputField5;
    
    textInputFields.push_back(textInputField1);
    textInputFields.push_back(textInputField2);
    textInputFields.push_back(textInputField3);
    textInputFields.push_back(textInputField4);
    textInputFields.push_back(textInputField5);
    
    // Add NFValues to the node with labels and set up textInputFields
    nfNode.addNFValue<DoubleNFValue, double>("Stepper", 3.14, textInputFields[0], 200, 200, 100, 20, font);
    nfNode.addNFValue<IntNFValue, int>("Accleration", 42, textInputFields[1], 200, 220, 100, 20, font);
    nfNode.addNFValue<BoolNFValue, bool>("Reset", false, textInputFields[2], 200, 240, 100, 20, font);
    nfNode.addNFValue<StringNFValue, std::string>("Mode", "Forward", textInputFields[3], 200, 260, 100, 20, font);
    nfNode.addNFValue<BoolNFValue, bool>("isReady", true, textInputFields[4], 200, 280, 100, 20, font);
}

//--------------------------------------------------------------
void ofApp::update(){

}
void drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    // Set color to blue (filled)
    ofSetColor(128, 128, 128);
    // Draw a filled rectangle at position (100, 100) with a width of 200 and height of 150
    ofDrawRectangle(x, y, width, height);

    // Set color to black (outline)
    ofSetColor(255);
    // Draw the same rectangle with no fill to create the outline
    ofNoFill();
    ofDrawRectangle(x, y, width, height);
    ofDrawRectangle(x + width, y, width, height);
    ofFill(); // Restore fill mode for subsequent drawings
}

//--------------------------------------------------------------
void ofApp::drawValue(){
    ofBackground(0);
    ofSetColor(255);
    
    // Access and modify NFValues in the order they were added
    const std::vector<NFValue*>& drawOrder = nfNode.getDrawOrder();
    size_t indexCounter=0;
    for (const auto& nfValue : drawOrder) {
        ofRectangle rect = textInputFields[indexCounter].bounds;
        drawPanel(rect.x, rect.y, rect.width, rect.height);
        ofSetColor(255);
        // adjust position for font rendering
        rect.x += 10;
        rect.y += 14;
        if (typeid(StringNFValue) == typeid(*nfValue)) {
            StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(nfValue);
            ofDrawBitmapString(strNFValue->value.getName(), rect.x, rect.y);
            ofDrawBitmapString(strNFValue->value.get(), rect.x+rect.width, rect.y);
            /*
            ofRect(textInputFields[indexCounter].bounds);
            ofNoFill();
            textInputFields[indexCounter].draw();
             */
            
        } else if (typeid(DoubleNFValue) == typeid(*nfValue)) {
            DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(nfValue);
            ofDrawBitmapString(doubleNFValue->value.getName(), rect.x, rect.y);
            ofDrawBitmapString(doubleNFValue->value.get(), rect.x+rect.width, rect.y);
            /*
            ofRect(textInputFields[indexCounter].bounds);
            ofNoFill();
            textInputFields[indexCounter].draw();
             */
        } else if (typeid(BoolNFValue) == typeid(*nfValue)) {
            BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(nfValue);
            ofDrawBitmapString(boolNFValue->value.getName(), rect.x, rect.y);
            bool isTrue = boolNFValue->value.get();
            if (isTrue) {
                ofDrawBitmapString("True", rect.x+rect.width, rect.y);
            } else {
                ofDrawBitmapString("False", rect.x+rect.width, rect.y);
            }
            
            /*
            ofRect(textInputFields[indexCounter].bounds);
            ofNoFill();
            textInputFields[indexCounter].draw();
             */
        } else if (typeid(IntNFValue) == typeid(*nfValue)) {
            IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(nfValue);
            ofDrawBitmapString(intNFValue->value.getName(), rect.x, rect.y);
            ofDrawBitmapString(intNFValue->value.get(), rect.x+rect.width, rect.y);
            /*
            ofRect(textInputFields[indexCounter].bounds);
            ofNoFill();
            textInputFields[indexCounter].draw();
             */
        }
        indexCounter++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    drawValue();
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
