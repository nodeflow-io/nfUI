#include "WaveformDemo.h"
#include "UI-Components/NfEventBus.hpp"

WaveformDemo::WaveformDemo() {
    // Initialize default parameters
    _signal1Params.amplitude = 1.0;
    _signal1Params.frequency = 50.0;
    _signal1Params.type = 0;  // Sine
    
    _signal2Params.amplitude = 0.5;
    _signal2Params.frequency = 30.0;
    _signal2Params.type = 2;  // Sawtooth
}

WaveformDemo::~WaveformDemo() {
    cleanup();
}

void WaveformDemo::setup(nfUI::NfUIConfig& config) {
    float width = 220;
    float margin = 10;
    float posX = 10;
    float posY = 120;
    
    // Signal 1 Node
    config.backgroundColor = ofColor(20,25,31);
    config.focusBackgroundColor = ofColor(35,38,42);
    config.focusColor = ofColor::black;
    config.bounds = ofRectangle(posX, posY, width, 20);
    config.isAbsolutePosition = true;
    config.setMargin(0);
    config.setPadding(0);
    config.contentHeight = 5;
    config.contentWidth = width-2*margin;
    config.isDebug = false;
    _signal1Node = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "Signal_1",
        "Signal Generator 1"
    );
    
    config.isAbsolutePosition = false;
    config.backgroundColor = ofColor(56, 62, 66, 128);
    config.focusBackgroundColor = ofColor(56, 62, 66, 255);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    _signal1Label = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "SIGNAL 1"
    );
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 4;
    config.showLabel = true;
    _signal1Amplitude = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::DoubleNFValue>(
        config,
        "Amplitude",
        _signal1Params.amplitude
    );
    
    _signal1Frequency = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::DoubleNFValue>(
        config,
        "Frequency",
        _signal1Params.frequency
    );
    
    // Create signal type selection options
    std::vector<std::string> signalTypeNames = {"Sine", "Square", "Sawtooth"};
    std::vector<int> signalTypeValues = {0, 1, 2};
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 255;
    config.showLabel = true;
    _signal1Type = nfUI::createUIElement<nfUI::NfSelection, nfUI::SelectionNFValue>(
        config,
        "Signal Type",
        signalTypeNames,
        signalTypeValues,
        _signal1Params.type
    );
    
    // Add all components to Signal 1 Node
    _signal1Node->addChild(_signal1Label);
    _signal1Node->addChild(_signal1Amplitude);
    _signal1Node->addChild(_signal1Frequency);
    _signal1Node->addChild(_signal1Type);
    
    // Signal 2 Node
    posX = 10;
    posY = 240;
    
    config.backgroundColor = ofColor(20,25,31);
    config.focusBackgroundColor = ofColor(35,38,42);
    config.focusColor = ofColor::black;
    config.bounds = ofRectangle(posX, posY, width, 20);
    config.isAbsolutePosition = true;
    config.setMargin(0);
    config.setPadding(0);
    config.contentHeight = 5;
    config.contentWidth = width-2*margin;
    config.isDebug = false;
    _signal2Node = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "Signal_2",
        "Signal Generator 2"
    );
    
    config.isAbsolutePosition = false;
    config.backgroundColor = ofColor(56, 62, 66, 128);
    config.focusBackgroundColor = ofColor(56, 62, 66, 255);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    _signal2Label = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "SIGNAL 2"
    );
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 4;
    config.showLabel = true;
    _signal2Amplitude = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::DoubleNFValue>(
        config,
        "Amplitude",
        _signal2Params.amplitude
    );
    
    _signal2Frequency = nfUI::createUIElement<nfUI::NfTextInputField, nfUI::DoubleNFValue>(
        config,
        "Frequency",
        _signal2Params.frequency
    );
    
    config.backgroundColor = ofColor(22,34,51);
    config.focusBackgroundColor = ofColor(13,20,30);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width-2*margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 255;
    config.showLabel = true;
    _signal2Type = nfUI::createUIElement<nfUI::NfSelection, nfUI::SelectionNFValue>(
        config,
        "Signal Type",
        signalTypeNames,
        signalTypeValues,
        _signal2Params.type
    );
    
    // Add all components to Signal 2 Node
    _signal2Node->addChild(_signal2Label);
    _signal2Node->addChild(_signal2Amplitude);
    _signal2Node->addChild(_signal2Frequency);
    _signal2Node->addChild(_signal2Type);
    
    // Add the signal generator nodes to the node manager
    nfUI::g_nodeManager.addNode(_signal1Node);
    nfUI::g_nodeManager.addNode(_signal2Node);
    
    // Register signal event handlers
    ofAddListener(_signal1Type->selectionChanged, this, &WaveformDemo::onSignal1TypeChanged);
    ofAddListener(_signal2Type->selectionChanged, this, &WaveformDemo::onSignal2TypeChanged);
    
    // Ensure signal UI components are properly initialized
    ensureSignalUIInitialized();
}

void WaveformDemo::update() {
    // Update signal parameters from UI components
    updateSignalParameters();
}

void WaveformDemo::draw() {
    // Draw signal waveforms
    drawSignalWaveforms();
}

void WaveformDemo::cleanup() {
    // Remove event listeners
    if (_signal1Type) {
        ofRemoveListener(_signal1Type->selectionChanged, this, &WaveformDemo::onSignal1TypeChanged);
    }
    
    if (_signal2Type) {
        ofRemoveListener(_signal2Type->selectionChanged, this, &WaveformDemo::onSignal2TypeChanged);
    }
    
    // Remove nodes from manager
    if (_signal1Node) {
        nfUI::g_nodeManager.removeNode("Signal_1");
    }
    
    if (_signal2Node) {
        nfUI::g_nodeManager.removeNode("Signal_2");
    }
    
    // Clear shared pointers
    _signal1Node = nullptr;
    _signal1Label = nullptr;
    _signal1Amplitude = nullptr;
    _signal1Frequency = nullptr;
    _signal1Type = nullptr;
    
    _signal2Node = nullptr;
    _signal2Label = nullptr;
    _signal2Amplitude = nullptr;
    _signal2Frequency = nullptr;
    _signal2Type = nullptr;
}

void WaveformDemo::onSignal1TypeChanged(nfUI::UIEventArgs& eventArgs) {
    // Get the selection value from the signal type control
    nfUI::SelectionNFValue* selectionValue = _signal1Type->selectionValue;
    if (selectionValue) {
        std::string typeName = selectionValue->getSelectedName();
        int typeValue = selectionValue->getSelectedValue();
        
        std::cout << "Signal 1 type changed to: " << typeName << " (value: " << typeValue << ")\n";
        
        // Update status bar with information about the change
        // In the demo context, we can't directly access _guiParams, so we'll just log
        std::cout << "Signal 1 type: " << typeName << std::endl;
    }
}

void WaveformDemo::onSignal2TypeChanged(nfUI::UIEventArgs& eventArgs) {
    // Get the selection value from the signal type control
    nfUI::SelectionNFValue* selectionValue = _signal2Type->selectionValue;
    if (selectionValue) {
        std::string typeName = selectionValue->getSelectedName();
        int typeValue = selectionValue->getSelectedValue();
        
        std::cout << "Signal 2 type changed to: " << typeName << " (value: " << typeValue << ")\n";
        
        // Update status bar with information about the change
        // In the demo context, we can't directly access _guiParams, so we'll just log
        std::cout << "Signal 2 type: " << typeName << std::endl;
    }
}

void WaveformDemo::updateSignalParameters() {
    // Make sure all UI components are initialized
    ensureSignalUIInitialized();
    
    // Update signal 1 parameters from UI components
    if (_signal1Amplitude && _signal1Amplitude->text.size() > 0) {
        _signal1Params.amplitude = nfAPI::toDouble(_signal1Amplitude->text);
    }
    
    if (_signal1Frequency && _signal1Frequency->text.size() > 0) {
        _signal1Params.frequency = nfAPI::toDouble(_signal1Frequency->text);
    }
    
    if (_signal1Type && _signal1Type->selectionValue) {
        try {
            _signal1Params.type = _signal1Type->selectionValue->getSelectedValue();
        } catch (const std::exception& e) {
            ofLogError("WaveformDemo") << "Error getting signal 1 type: " << e.what();
        }
    }
    
    // Update signal 2 parameters from UI components
    if (_signal2Amplitude && _signal2Amplitude->text.size() > 0) {
        _signal2Params.amplitude = nfAPI::toDouble(_signal2Amplitude->text);
    }
    
    if (_signal2Frequency && _signal2Frequency->text.size() > 0) {
        _signal2Params.frequency = nfAPI::toDouble(_signal2Frequency->text);
    }
    
    if (_signal2Type && _signal2Type->selectionValue) {
        try {
            _signal2Params.type = _signal2Type->selectionValue->getSelectedValue();
        } catch (const std::exception& e) {
            ofLogError("WaveformDemo") << "Error getting signal 2 type: " << e.what();
        }
    }
}

void WaveformDemo::ensureSignalUIInitialized() {
    // Make sure signal 1 components have proper values
    if (_signal1Amplitude && !_signal1Amplitude->text.size()) {
        auto value = std::make_unique<nfUI::DoubleNFValue>(_signal1Params.amplitude);
        _signal1Amplitude->setValue(std::move(value));
    }
    
    if (_signal1Frequency && !_signal1Frequency->text.size()) {
        auto value = std::make_unique<nfUI::DoubleNFValue>(_signal1Params.frequency);
        _signal1Frequency->setValue(std::move(value));
    }
    
    if (_signal1Type && _signal1Type->selectionValue == nullptr) {
        // Force a draw to initialize selectionValue (it's initialized in NfSelection::draw)
        _signal1Type->draw();
        
        // If still null, create a selection with default options
        if (_signal1Type->selectionValue == nullptr) {
            ofLogWarning("WaveformDemo") << "Signal 1 type selection value is null, reinitializing";
            
            // Create signal type selection options
            std::vector<std::string> signalTypeNames = {"Sine", "Square", "Sawtooth"};
            std::vector<int> signalTypeValues = {0, 1, 2};
            
            auto value = std::make_unique<nfUI::SelectionNFValue>(signalTypeNames, signalTypeValues, 0);
            _signal1Type->setValue(std::move(value));
        }
    }
    
    // Make sure signal 2 components have proper values
    if (_signal2Amplitude && !_signal2Amplitude->text.size()) {
        auto value = std::make_unique<nfUI::DoubleNFValue>(_signal2Params.amplitude);
        _signal2Amplitude->setValue(std::move(value));
    }
    
    if (_signal2Frequency && !_signal2Frequency->text.size()) {
        auto value = std::make_unique<nfUI::DoubleNFValue>(_signal2Params.frequency);
        _signal2Frequency->setValue(std::move(value));
    }
    
    if (_signal2Type && _signal2Type->selectionValue == nullptr) {
        // Force a draw to initialize selectionValue (it's initialized in NfSelection::draw)
        _signal2Type->draw();
        
        // If still null, create a selection with default options
        if (_signal2Type->selectionValue == nullptr) {
            ofLogWarning("WaveformDemo") << "Signal 2 type selection value is null, reinitializing";
            
            // Create signal type selection options
            std::vector<std::string> signalTypeNames = {"Sine", "Square", "Sawtooth"};
            std::vector<int> signalTypeValues = {0, 1, 2};
            
            auto value = std::make_unique<nfUI::SelectionNFValue>(signalTypeNames, signalTypeValues, 2);
            _signal2Type->setValue(std::move(value));
        }
    }
}

double WaveformDemo::generateSample(const SignalParams& params, double time) {
    switch (params.type) {
        case 0: // Sine
            return generateSine(params.amplitude, params.frequency, time);
        case 1: // Square
            return generateSquare(params.amplitude, params.frequency, time);
        case 2: // Sawtooth
            return generateSawtooth(params.amplitude, params.frequency, time);
        default:
            return 0.0;
    }
}

double WaveformDemo::generateSine(double amplitude, double frequency, double time) {
    return amplitude * sin(2.0 * M_PI * frequency * time);
}

double WaveformDemo::generateSquare(double amplitude, double frequency, double time) {
    double phase = fmod(frequency * time, 1.0);
    return amplitude * (phase < 0.5 ? 1.0 : -1.0);
}

double WaveformDemo::generateSawtooth(double amplitude, double frequency, double time) {
    double phase = fmod(frequency * time, 1.0);
    return amplitude * (2.0 * phase - 1.0);
}

void WaveformDemo::drawSignalWaveforms() {
    const int width = 200;
    const int height = 100;
    const float xOffset1 = 800;
    const float yOffset1 = 150;
    const float xOffset2 = 800;
    const float yOffset2 = 350;
    
    // Draw signal 1 background
    ofPushStyle();
    ofSetColor(20, 25, 31);
    ofDrawRectangle(xOffset1, yOffset1 - height/2, width, height);
    
    // Draw signal 1 label
    ofSetColor(200, 200, 200);
    ofDrawBitmapString("Signal 1 Waveform", xOffset1 + 10, yOffset1 - height/2 + 15);
    
    // Draw signal 1 waveform
    ofSetColor(41, 225, 255);  // Cyan color for signal 1
    ofNoFill();
    ofBeginShape();
    double time = ofGetElapsedTimef();
    for (int x = 0; x < width; x++) {
        double normalizedX = x / (double)width;
        double sampleTime = time + normalizedX * 0.01;  // Spread samples over 10ms
        double sample = generateSample(_signal1Params, sampleTime);
        ofVertex(xOffset1 + x, yOffset1 + sample * height/2);
    }
    ofEndShape(false);
    
    // Draw signal 2 background
    ofSetColor(20, 25, 31);
    ofDrawRectangle(xOffset2, yOffset2 - height/2, width, height);
    
    // Draw signal 2 label
    ofSetColor(200, 200, 200);
    ofDrawBitmapString("Signal 2 Waveform", xOffset2 + 10, yOffset2 - height/2 + 15);
    
    // Draw signal 2 waveform
    ofSetColor(255, 121, 0);  // Orange color for signal 2
    ofNoFill();
    ofBeginShape();
    for (int x = 0; x < width; x++) {
        double normalizedX = x / (double)width;
        double sampleTime = time + normalizedX * 0.01;  // Spread samples over 10ms
        double sample = generateSample(_signal2Params, sampleTime);
        ofVertex(xOffset2 + x, yOffset2 + sample * height/2);
    }
    ofEndShape(false);
    ofPopStyle();
} 