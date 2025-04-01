//
//  NfPanel.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#include "NfPanel.hpp"

namespace nfUI {

void NfPanel::draw() {
    ofPushMatrix();
    NfBoxxer::draw(); // Call base class draw for common drawing
    
    if (_firstRender) {
        ofRegisterMouseEvents(this);
        if (_config.isDebug) {
            std::cout << "NfPanel: " << _name << std::endl;
        }
        _firstRender = false;
        markDimensionsDirty();  // Ensure dimensions are calculated on first render
    }

    if (nodeIsFocused || isFocused.get()) {
        ofSetColor(focusBackgroundColor.get());
    } else {
        ofSetColor(backgroundColor.get());
    }
    
    // get Dimensions children requires
    float width, height;
    this->getDimensions(width, height);
    _config.width = width;
    _config.height = height;
    
    // draw own content
    ofDrawRectangle(0, 0, _config.width, _config.height);
    
    // call drawChildren with the current paddings
    drawChildren(_config.paddingLeft, _config.paddingTop);
    
    ofPopMatrix(); // Restore the drawing context
}

void NfPanel::mouseDragged(ofMouseEventArgs& args) {
}

void NfPanel::mousePressed(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        if (!this->nodeIsFocused) {
            nfUI::NfEventManager::getEventManager().emit("node_focus", this->_name);
            markDimensionsDirty();  // Mark dimensions as dirty when focus changes
        }
    }
}

void NfPanel::mouseMoved(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        parameters.getBool("IsFocused") = true;
        markDimensionsDirty();  // Mark dimensions as dirty when mouse moves
    } else {
        parameters.getBool("IsFocused") = false;
    }
}

void NfPanel::mouseScrolled(ofMouseEventArgs& args) {
}

void NfPanel::mouseEntered(ofMouseEventArgs& args) {
}

void NfPanel::mouseExited(ofMouseEventArgs& args) {
}

void NfPanel::mouseReleased(ofMouseEventArgs& args) {
}

} // namespace nfUI
