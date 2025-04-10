#include "DemoManager.h"
#include "UI-Components/NfEventBus.hpp"
#include "UI-Components/NfUIConfig.hpp"

DemoManager::DemoManager() : _activeDemoType(DemoType::NONE) {
}

DemoManager::~DemoManager() {
    cleanup();
}

void DemoManager::setup(nfUI::NfUIConfig& config) {
    // Initialize the demo selector UI
    initializeDemoSelector(config);
    
    // No active demo at startup
    _activeDemoType = DemoType::NONE;
}

void DemoManager::update() {
    // Update the active demo if one is selected
    switch (_activeDemoType) {
        case DemoType::WAVEFORM:
            if (_waveformDemo) {
                _waveformDemo->update();
            }
            break;
        case DemoType::NONE:
        default:
            // No demo to update
            break;
    }
}

void DemoManager::draw() {
    // Draw the active demo if one is selected
    switch (_activeDemoType) {
        case DemoType::WAVEFORM:
            if (_waveformDemo) {
                _waveformDemo->draw();
            }
            break;
        case DemoType::NONE:
        default:
            // No demo to draw
            break;
    }
}

void DemoManager::cleanup() {
    // Clean up any active demo
    setActiveDemo(DemoType::NONE);
    
    // Remove event listener
    if (_demoSelector) {
        ofRemoveListener(_demoSelector->selectionChanged, this, &DemoManager::onDemoSelectionChanged);
    }
    
    // Remove nodes from manager
    if (_demoSelectorNode) {
        nfUI::g_nodeManager.removeNode("DemoSelector");
    }
    
    // Clear shared pointers
    _demoSelectorNode = nullptr;
    _demoSelectorLabel = nullptr;
    _demoSelector = nullptr;
}

void DemoManager::setActiveDemo(DemoType demoType) {
    // First, clean up the current demo if there is one
    switch (_activeDemoType) {
        case DemoType::WAVEFORM:
            if (_waveformDemo) {
                _waveformDemo->cleanup();
                _waveformDemo.reset();
            }
            break;
        case DemoType::NONE:
        default:
            // No cleanup needed
            break;
    }
    
    // Update the active demo type
    _activeDemoType = demoType;
    
    // Initialize the new demo if needed
    nfUI::NfUIConfig config; // Create a default config
    switch (_activeDemoType) {
        case DemoType::WAVEFORM:
            _waveformDemo = std::make_unique<WaveformDemo>();
            if (_waveformDemo) {
                _waveformDemo->setup(config);
            }
            break;
        case DemoType::NONE:
        default:
            // No initialization needed
            break;
    }
}

void DemoManager::onDemoSelectionChanged(nfUI::UIEventArgs& eventArgs) {
    if (_demoSelector && _demoSelector->selectionValue) {
        int selectedValue = _demoSelector->selectionValue->getSelectedValue();
        std::string selectedName = _demoSelector->selectionValue->getSelectedName();
        
        std::cout << "Selected demo: " << selectedName << " (value: " << selectedValue << ")" << std::endl;
        
        // Set the active demo based on the selection
        switch (selectedValue) {
            case 1:
                setActiveDemo(DemoType::WAVEFORM);
                break;
            case 0:
            default:
                setActiveDemo(DemoType::NONE);
                break;
        }
    }
}

void DemoManager::initializeDemoSelector(nfUI::NfUIConfig& config) {
    float width = 220;
    float margin = 10;
    float posX = 10;
    float posY = 40;
    
    // Demo selector node
    config.backgroundColor = ofColor(20, 25, 31);
    config.focusBackgroundColor = ofColor(35, 38, 42);
    config.focusColor = ofColor::black;
    config.bounds = ofRectangle(posX, posY, width, 20);
    config.isAbsolutePosition = true;
    config.setMargin(0);
    config.setPadding(0);
    config.contentHeight = 5;
    config.contentWidth = width - 2 * margin;
    config.isDebug = false;
    _demoSelectorNode = nfUI::createUIElement<nfUI::NfPanel, nfUI::StringNFValue>(
        config,
        "DemoSelector",
        "Demo Selector"
    );
    
    // Demo selector label
    config.isAbsolutePosition = false;
    config.backgroundColor = ofColor(56, 62, 66, 128);
    config.focusBackgroundColor = ofColor(56, 62, 66, 255);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width, 30);
    config.setMargin(0);
    config.setPadding(10);
    config.contentHeight = 5;
    _demoSelectorLabel = nfUI::createUIElement<nfUI::NfLabel, nfUI::StringNFValue>(
        config,
        "Label",
        "DEMO SELECTOR"
    );
    
    // Create demo options
    std::vector<std::string> demoNames = {"None", "Waveform"};
    std::vector<int> demoValues = {0, 1};
    
    // Demo selection dropdown
    config.backgroundColor = ofColor(22, 34, 51);
    config.focusBackgroundColor = ofColor(13, 20, 30);
    config.focusColor = ofColor::yellow;
    config.bounds = ofRectangle(posX, posY, width - 2 * margin, 20);
    config.setMargin(8, 10, 0, 8);
    config.setPadding(5, 10, 5, 10);
    config.maxTextLength = 255;
    config.showLabel = true;
    _demoSelector = nfUI::createUIElement<nfUI::NfSelection, nfUI::SelectionNFValue>(
        config,
        "Active Demo",
        demoNames,
        demoValues,
        0  // Initially no demo
    );
    
    // Add components to the node
    _demoSelectorNode->addChild(_demoSelectorLabel);
    _demoSelectorNode->addChild(_demoSelector);
    
    // Add node to the manager
    nfUI::g_nodeManager.addNode(_demoSelectorNode);
    
    // Register event handler
    ofAddListener(_demoSelector->selectionChanged, this, &DemoManager::onDemoSelectionChanged);
} 