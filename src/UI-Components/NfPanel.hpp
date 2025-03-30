//
//  NfPanel.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#ifndef NfPanel_hpp
#define NfPanel_hpp

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
#include "NfEventManager.hpp"

namespace nfUI {

class NfPanel : public NfBoxxer {
    
private:
    bool _firstRender = true;   // Flag to track if draw() was called for the first time
    bool _isDragging = false;   // Flag to track if the panel is being dragged
    ofPoint _dragStartPos;      // Starting point of a drag
    ofPoint _panelStartPos;     // Offset from the initial drag point
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // Event declaration
    ofEvent<UIEventArgs> clicked;
    
    // Core functionality
    void draw();
    
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

#endif /* NfPanel_hpp */
