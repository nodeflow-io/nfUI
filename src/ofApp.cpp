#include "ofApp.h"
#include "UI-Components/NfEventBus.hpp"
#include "UI-Components/NfSelection.hpp"


//--------------------------------------------------------------
void ofApp::setup() {
    // Initialize the event bus now that the OF window is ready
    BUS.setupOFEvents();
    
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
    
    // in this case we use an alpha value because focused elements 
    config.backgroundColor = ofColor(255,0,0,150);
    config.focusBackgroundColor = ofColor(0,255,0,150);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 1;
    config.showLabel = true;
    _guiParamsShowGrid = nfUI::createUIElement<nfUI::NfToggleSwitch, nfUI::BoolNFValue>(
        config,
        "Show Grid",
        _guiParams.getShowGrid()
    );
    

    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
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
    
    // in this case we use an alpha value because focused elements
    config.backgroundColor = ofColor(255,0,0,150);
    config.focusBackgroundColor = ofColor(0,255,0,150);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 1;
    config.showLabel = true;
    _guiParamsShowStatusBar = nfUI::createUIElement<nfUI::NfToggleSwitch, nfUI::BoolNFValue>(
        config,
        "Show StatBar",
         _guiParams.getShowStatusBar()
    );
    
    _guiParamsShowStatusFPS = nfUI::createUIElement<nfUI::NfToggleSwitch, nfUI::BoolNFValue>(
        config,
        "Show FPS",
         _guiParams.getShowFPS()
    );
    
    
    config.backgroundColor = ofColor(46, 80, 117);
    config.focusBackgroundColor = ofColor::yellow;
    config.focusColor = ofColor::black;
    config.marginBottom = 8;  // TODO: this should not be necessary
    _guiParamsButton = nfUI::createUIElement<nfUI::NfButton, nfUI::StringNFValue>(
        config,
        "Button",
        "Set GUI-Parameters"
    );

    // Create selection options
    std::vector<std::string> waveformNames = {"Sine", "Square", "Mixed"};
    std::vector<int> waveformValues = {0, 1, 2}; // Corresponding values for each option
    // auto waveformSelection = std::make_shared<nfUI::SelectionNFValue>(waveformNames, waveformValues, 0); // 0 = Sine selected - No longer needed here
    
    // Create and add the selection component, passing constructor args directly
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 255;
    config.showLabel = true;
    _guiParamsWaveform = nfUI::createUIElement<nfUI::NfSelection, nfUI::SelectionNFValue>(
        config,
        "Waveform",
        waveformNames, // Pass constructor arguments directly
        waveformValues,
        0             // Initial index (Sine)
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
    _guiParamsNode->addChild(_guiParamsShowStatusBar);
    _guiParamsNode->addChild(_guiParamsShowStatusFPS);
    _guiParamsNode->addChild(_guiParamsWaveform);  // Add waveform selector before the button
    _guiParamsNode->addChild(_guiParamsButton);
    // add event handlers for interactive elements
     ofAddListener(_guiParamsShowGrid->clicked, this, &ofApp::onGuiParametersShowGridClicked);
     ofAddListener(_guiParamsShowStatusBar->clicked, this, &ofApp::onGuiParametersShowStatusBarClicked);
     ofAddListener(_guiParamsShowStatusFPS->clicked, this, &ofApp::onGuiParametersShowStatusFPSClicked);
     ofAddListener(_guiParamsButton->clicked, this, &ofApp::onGuiParametersButtonClicked);
    
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
    
    // adding childs to inspector widget here
    _inspectorNode->addChild(_inspectorLabel);
    _inspectorNode->addChild(_inspectorPosX);
    _inspectorNode->addChild(_inspectorPosY);
    _inspectorNode->addChild(_inspectorButton);
    // add event handlers for interactive element
     ofAddListener(_inspectorButton->clicked, this, &ofApp::onInspectorButtonClicked);
    
    // adding widgets to NodeManager
    nfUI::g_nodeManager.addNode(_guiParamsNode); // Add the GUI Parameters to the node manager
    nfUI::g_nodeManager.addNode(_inspectorNode); // Add the inspector to the node manager
    
    // Subscribe to position change events
    BUS.subscribe(nfUI::AppEventType::POSITION_CHANGED, [this](const nfUI::Event& event) {
        // Only update inspector if the changed node is _guiParamsNode
        if (event.sender == _guiParamsNode.get()) {
            ofPoint newPos = event.payload_as<ofPoint>();
            
            // Update the inspector X position field
            auto xValue = std::make_unique<nfUI::IntNFValue>(static_cast<int>(newPos.x));
            _inspectorPosX->setValue(std::move(xValue));
            
            // Update the inspector Y position field
            auto yValue = std::make_unique<nfUI::IntNFValue>(static_cast<int>(newPos.y));
            _inspectorPosY->setValue(std::move(yValue));
        }
    }, this);
    
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
    nfUI::g_nodeManager.drawNodes(); // This starts the recursive drawing process
    
    ofPopMatrix(); // Restore the transformation matrix
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Perform actions based on the pressed key
    switch (key) {
        case OF_KEY_F1: {
            // F1 key pressed
            _guiParams.setShowGrid(!_guiParams.getShowGrid());
            std::cout << "ofApp::keyPressed _showGrid: " << _guiParams.getShowGrid() << "\n";
            // Create a std::unique_ptr to BoolNFValue
            auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowGrid());
            // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
            _guiParamsShowGrid->setValue(std::move(boolNFtemp));
            }
            break;
        case OF_KEY_F2: {
            // F2 key pressed
            _guiParams.setShowStatusBar(!_guiParams.getShowStatusBar());
            std::cout << "ofApp::keyPressed _showStatusBar: "  << _guiParams.getShowStatusBar() << "\n";
            // Create a std::unique_ptr to BoolNFValue
            auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowStatusBar());
            // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
            _guiParamsShowStatusBar->setValue(std::move(boolNFtemp));
            }
            break;
        case OF_KEY_F3: {
            // F3 key pressed
            _guiParams.setShowFPS(!_guiParams.getShowFPS());
            std::cout << "ofApp::keyPressed _showFPS: "  << _guiParams.getShowFPS() << "\n";
            // Create a std::unique_ptr to BoolNFValue
            auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowFPS());
            // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
            _guiParamsShowStatusFPS->setValue(std::move(boolNFtemp));
        }
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

void ofApp::onGuiParametersShowGridClicked(nfUI::UIEventArgs& eventArgs) {
    std::cout << "ofApp::onGuiParametersShowGridClicked\n";
    _guiParams.setShowGrid(!_guiParams.getShowGrid());
    
    // Create a std::unique_ptr to BoolNFValue
    auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowGrid());
    // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
    _guiParamsShowGrid->setValue(std::move(boolNFtemp));
}

void ofApp::onGuiParametersShowStatusBarClicked(nfUI::UIEventArgs& eventArgs) {
    std::cout << "ofApp::onGuiParametersShowStatusBarClicked\n";
    _guiParams.setShowStatusBar(!_guiParams.getShowStatusBar());
    
    // Create a std::unique_ptr to BoolNFValue
    auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowStatusBar());
    // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
    _guiParamsShowStatusBar->setValue(std::move(boolNFtemp));
}

void ofApp::onGuiParametersShowStatusFPSClicked(nfUI::UIEventArgs& eventArgs) {
    std::cout << "ofApp::onGuiParametersShowStatusFPSClicked\n";
    _guiParams.setShowFPS(!_guiParams.getShowFPS());
    
    // Create a std::unique_ptr to BoolNFValue
    auto boolNFtemp = std::make_unique<nfUI::BoolNFValue>(_guiParams.getShowFPS());
    // Assuming _guiParamsShowGrid->setValue expects a std::unique_ptr<NFValue>
    _guiParamsShowStatusFPS->setValue(std::move(boolNFtemp));
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
void ofApp::mouseMoved(int x, int y){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    // NfEventBus now handles this automatically
}

/*
//--------------------------------------------------------------
void ofApp::windowEntered(int x, int y){
    // NfEventBus now handles this automatically
}

//--------------------------------------------------------------
void ofApp::windowExited(int x, int y){
    // NfEventBus now handles this automatically
}
*/

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
