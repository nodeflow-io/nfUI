//
//  NfButton.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef NfButton_hpp
#define NfButton_hpp

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

class NfButton : public NfBoxxer {
    
protected:
    bool _firstRender = true;   // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset; // font size dependant
    uint32_t horizontalTextOffset;
    bool mouseDownInRect;
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // Event declaration
    ofEvent<UIEventArgs> clicked;
    
    // Core functionality
    void draw() override;
    
    // Mouse event handlers
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseMoved(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args);
    void mouseEntered(ofMouseEventArgs& args);
    void mouseExited(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
};

} // namespace nfUI

#endif /* NfButton_hpp */
