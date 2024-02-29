//
//  NfPanel.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#ifndef NfPanel_hpp
#define NfPanel_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

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
    
    void draw() override {
        ofPushMatrix();
        NfBoxxer::draw(); // Call base class draw for common drawing
        
        if (_firstRender) {
            ofRegisterMouseEvents(this);
            if (_config.isDebug) {
                std::cout << "NfPanel: " << _name << std::endl;
            }
            _firstRender=false;
        }

        if (isFocused.get()) {
            ofSetColor(focusBackgroundColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }
        
        // get Dimensions children requires
        this->getDimensions(_config.width, _config.height);
        // draw own content
        ofDrawRectangle(0, 0, _config.width, _config.height);
        
        // call drawChildren with the current paddings
        drawChildren(_config.paddingLeft, _config.paddingTop);
        
        ofPopMatrix(); // Restore the drawing context
    }
    
    // mouse event handling -------------------
    
    void mouseDragged(ofMouseEventArgs& args) {
    }
    
    void mousePressed(ofMouseEventArgs& args) {
    }
    
    void mouseMoved(ofMouseEventArgs& args) {
        if(boundsMouse.inside(args.x, args.y)) {
            parameters.getBool("IsFocused") = true;
            // ofSetCursor(OF_CURSOR_HAND);
        } else {
            parameters.getBool("IsFocused") = false;
            // ofSetCursor(OF_CURSOR_ARROW);
        }
    }
    
    void mouseScrolled(ofMouseEventArgs& args) {
    }
    
    void mouseEntered(ofMouseEventArgs& args) {

    }
    
    void mouseExited(ofMouseEventArgs& args) {
 
    }

    void mouseReleased(ofMouseEventArgs& args) {
    }
};

}


#endif /* NfPanel_hpp */
