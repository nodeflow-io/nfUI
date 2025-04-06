//
//  NfLabel.hpp
//  nodeflowUI
//
//  Created by Matthias Srohmaier on 23.02.24.
//

#ifndef NfLabel_hpp
#define NfLabel_hpp

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

class NfLabel : public NfBoxxer {
    
private:
    bool _firstRender = true;   // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset;// font size dependant
    uint32_t horizontalTextOffset;
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
    
    // Event handling
    bool handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) override;
};

} // namespace nfUI

#endif /* NfLabel_hpp */
