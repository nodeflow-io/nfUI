#pragma once

#include "ofMain.h"
#include "nfUIElement.hpp"
#include "NfNodeManager.hpp"
#include "NfBoxxer.hpp"
#include "NfPanel.hpp"
#include "NfLabel.hpp"
#include "NfToggleSwitch.hpp"
#include "NfButton.hpp"
#include "NfTextInputField.hpp"
#include "NFValue.hpp"
#include "NfSelection.hpp"
#include "NfDom.hpp"
#include "GUIParams.hpp"

class WaveformDemo {
public:
    // Constructor/destructor
    WaveformDemo();
    ~WaveformDemo();
    
    // Main demo methods
    void setup(nfUI::NfUIConfig& config);
    void update();
    void draw();
    void cleanup();
    
private:
    // Signal generator event handlers
    void onSignal1TypeChanged(nfUI::UIEventArgs& eventArgs);
    void onSignal2TypeChanged(nfUI::UIEventArgs& eventArgs);
    
    // Signal 1 Generator Node
    std::shared_ptr<nfUI::NfBoxxer> _signal1Node;
    std::shared_ptr<nfUI::NfBoxxer> _signal1Label;
    std::shared_ptr<nfUI::NfBoxxer> _signal1Amplitude;
    std::shared_ptr<nfUI::NfBoxxer> _signal1Frequency;
    std::shared_ptr<nfUI::NfSelection> _signal1Type;
    
    // Signal 2 Generator Node
    std::shared_ptr<nfUI::NfBoxxer> _signal2Node;
    std::shared_ptr<nfUI::NfBoxxer> _signal2Label;
    std::shared_ptr<nfUI::NfBoxxer> _signal2Amplitude;
    std::shared_ptr<nfUI::NfBoxxer> _signal2Frequency;
    std::shared_ptr<nfUI::NfSelection> _signal2Type;
    
    // Signal generation properties
    struct SignalParams {
        double amplitude = 1.0;
        double frequency = 440.0;
        int type = 0;  // 0 = Sine, 1 = Square, 2 = Sawtooth
    };
    
    SignalParams _signal1Params;
    SignalParams _signal2Params;
    
    // Methods for signal generation
    void updateSignalParameters();
    double generateSample(const SignalParams& params, double time);
    double generateSine(double amplitude, double frequency, double time);
    double generateSquare(double amplitude, double frequency, double time);
    double generateSawtooth(double amplitude, double frequency, double time);
    void drawSignalWaveforms();
    
    // Helper method to ensure UI components are properly initialized
    void ensureSignalUIInitialized();
}; 