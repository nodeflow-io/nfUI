#include "ofApp.h"

void ofApp::setupTxt() {
    
    monoLineTextInput.setup();
    monoLineTextInput.text = "hello world";
    monoLineTextInput.bounds.x = 20;
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
    multilineTextInput.bounds.x = 20;
    multilineTextInput.bounds.y = 150;
    multilineTextInput.bounds.width = 500;
    multilineTextInput.bounds.height = 500;
    multilineTextInput.multiline = true;
    // Load a TrueType font file (replace "your_font.ttf" with the actual filename)
    if (font.loadFont("Roboto-Thin.ttf", 18)) {
        // Font loaded successfully, you can use it now
    } else {
        // Handle the case where the font failed to load
        ofLogError() << "Failed to load font!";
    }
    monoLineTextInput.setFont(font);
    
    
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    ofTrueTypeFont font;
    font.load(OF_TTF_SERIF, 18);
    _nfGUI.setup();
    setupTxt();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::drawTxt() {
    ofBackground(255*.15);
    
    ofSetColor(255);
    // Draw a rounded rectangle for monoLineTextInput
    ofDrawRectRounded(monoLineTextInput.bounds, 5); // Adjust the corner radius as needed
    // Draw a rounded rectangle for multilineTextInput
    ofDrawRectRounded(multilineTextInput.bounds, 5); // Adjust the corner radius as needed
    ofNoFill();
    ofSetColor(0);
    monoLineTextInput.draw();
    multilineTextInput.draw();
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    _nfGUI.draw();
    ofSetColor(0);
    // drawTxt();
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
