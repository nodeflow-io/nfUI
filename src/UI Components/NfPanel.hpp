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
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        ofPushMatrix();
        // NfBoxxer::draw(); // Call base class draw for common drawing code if needed
        
        // Button-specific drawing code here
        if (_firstRender) {
            std::cout << "NfPanel: " << _name << std::endl;
            _firstRender=false;
        }
        // For example, draw a rectangle with a different color when focused
        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }
        // decide wheter we need to translate
        if (_config.isAbsolutePosition) {
            ofTranslate(bounds.x, bounds.y);
        }
        
        // get subchildren width, height
        this->getDimensions(_config.width, _config.height);
        // draw own content
        ofDrawRectangle(0, 0, _config.width, _config.height);
        
        // translate paddings
        ofPushMatrix();
        ofTranslate(_config.paddingLeft, _config.paddingTop);
        
        // render children
        for (size_t i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            if (i) {
                auto& lastChild = children[i-1];
                float width, height;
                this->getChildDimensions(lastChild, width, height);
                ofTranslate(0, height);
            }
            child->draw();
        }
        ofPopMatrix();
        
        ofPopMatrix(); // Restore the drawing context
    }
};

}


#endif /* NfPanel_hpp */
