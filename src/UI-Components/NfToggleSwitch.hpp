//
//  NfToggleSwitch.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#ifndef NfToggleSwitch_hpp
#define NfToggleSwitch_hpp

// Standard library includes
#include <string>

// Forward declarations
namespace nfUI {
    class NfBoxxer;
    class UIEventArgs;
    class NFValue;
}

// Project includes
#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfToggleSwitch : public NfBoxxer {
    
private:
    bool _firstRender = true;           // Flag to track if draw() was called for the first time
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // Event declaration
    ofEvent<UIEventArgs> clicked;
    
    // Member variables
    NFValue* valueRawPtr;
    
    // Core functionality
    void draw();
    
    // Event handling
    bool handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) override;
};

} // namespace nfUI

#endif /* NfToggleSwitch_hpp */
