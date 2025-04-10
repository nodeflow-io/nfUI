#pragma once

#include "ofMain.h"
#include "nfUIElement.hpp"
#include "NfNodeManager.hpp"
#include "NfBoxxer.hpp"
#include "NfPanel.hpp"
#include "NfSelection.hpp"
#include "waveform/WaveformDemo.h"

// Forward declaration
namespace nfUI {
    class NfUIConfig;
}

enum class DemoType {
    NONE,
    WAVEFORM
    // Add new demo types here as they're created
};

class DemoManager {
public:
    DemoManager();
    ~DemoManager();
    
    void setup(nfUI::NfUIConfig& config);
    void update();
    void draw();
    void cleanup();
    
    // Method to change the active demo
    void setActiveDemo(DemoType demoType);
    
private:
    // Demo selection UI
    std::shared_ptr<nfUI::NfBoxxer> _demoSelectorNode;
    std::shared_ptr<nfUI::NfBoxxer> _demoSelectorLabel;
    std::shared_ptr<nfUI::NfSelection> _demoSelector;
    
    // Currently active demo type
    DemoType _activeDemoType;
    
    // Actual demo instances
    std::unique_ptr<WaveformDemo> _waveformDemo;
    
    // Event handlers
    void onDemoSelectionChanged(nfUI::UIEventArgs& eventArgs);
    
    // Helper methods
    void initializeDemoSelector(nfUI::NfUIConfig& config);
}; 