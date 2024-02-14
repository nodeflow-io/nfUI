#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);

    // Initialize parameters
    floatParams.emplace_back("Float Param 1", 0.0, 0.0, 10.0);
    floatParams.emplace_back("Float Param 2", 5.0, 0.0, 10.0);

    intParams.emplace_back("Int Param 1", 5, 0, 10);
    intParams.emplace_back("Int Param 2", 2, 0, 5);

    // Create GUI elements
    float y = 10;  // Initial y-position
    for (auto& param : floatParams) {
        auto guiElement = std::make_shared<ofxFloatSlider>();
        guiElement->setup(param);
        guiElement->setPosition(10, y);  // Set position
        guiElements.push_back(guiElement);
        y += 30;  // Adjust vertical spacing
    }

    for (auto& param : intParams) {
        auto guiElement = std::make_shared<ofxIntSlider>();
        guiElement->setup(param);
        guiElement->setPosition(10, y);  // Set position
        guiElements.push_back(guiElement);
        y += 30;  // Adjust vertical spacing
    }

    // Set GUI position and size
    gui.setPosition(10, 10);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    /// Draw the GUI panel
    for (auto& element : guiElements) {
        element->draw();
    }
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
