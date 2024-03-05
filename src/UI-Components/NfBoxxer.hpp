//
//  NfBoxxer.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef NfBoxxer_hpp
#define NfBoxxer_hpp

#include "nfUIElement.hpp"
#include "NfModalType.h"

namespace nfUI {

class NfBoxxer : public NfUIElement {
    
private:
    using ListenerID = size_t;
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    ListenerID listenerID;

public:
    std::string _name;
    NfUIConfig _config;
    bool nodeIsFocused = false;


    // Updated constructor
    NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue)
            : NfUIElement(config, std::move(initialValue), name), 
              _config(config), _name(name) {
            // Your initialization code here
        }
    
    // this implements the base class
    // put out debug infos like paddings and margins
    void draw() {
        if (_firstRender) {
            if (_config.isDebug) {
                std::cout << "Boxxer: First render of " << _name << std::endl;
                NFValue* valueRawPtr = this->getValue();
                if (valueRawPtr != nullptr) {
                    std::string valueAsString = valueRawPtr->toString();
                    std::cout << "Boxxer: Value as string: " << valueAsString << std::endl;
                } else {
                    std::cout << "Boxxer: No value available." << std::endl;
                }
            }
        }
        // this is used for keeping track of the bounds for mouse interactions
        // If we are drawing the root element we reset it for all children too
        if (this->isRoot()) {
            // this->boundsMouse.x =
            for (size_t i = 0; i < children.size(); ++i) {
                auto& child = children[i];
                child->boundsMouse=child->bounds;
            }
        }
        
        // decide wheter we need to translate to an absolute position
        if (_config.isAbsolutePosition) {
            ofTranslate(bounds.x, bounds.y);
            // if this is not the root element we need to translate
            // the mousebounds to its new absolute position
            // because mousevents are happening in absolute coordinates
            if (!this->isRoot()) {
                translateBounds(boundsMouse, bounds.x, bounds.y, _name);
            }
            if (_config.isDebug) {
                std::cout << "Boxxer: " << _name << " absolute position: " << bounds.x << "," << bounds.y << std::endl;
            }
        }
        
        // decide wheter we need to translate the margins
        if (_config.marginTop || _config.marginLeft) {
            ofTranslate(_config.marginLeft, _config.marginTop);
            translateBounds(boundsMouse, _config.marginLeft, _config.marginTop, _name);
            if (_config.isDebug) {
                std::cout << "Boxxer: " << _name << " margin: " << _config.marginLeft << "," << _config.marginTop << std::endl;
            }
        }
        
        if (_config.isDebug) {
            std::cout << "Boxxer: " << _name << " mB: " << boundsMouse.x << " " << boundsMouse.y << std::endl;
        }
        // After the first render, set the flag to false
        if (_firstRender) {
            _firstRender = false;
        }
    }

    
    void drawChildren (const float& paddingLeft, const float& paddingTop) {
        std::string name;
        ofPushMatrix();
        ofTranslate(paddingLeft, paddingTop);
        name = "padding: "+_name;
        translateBounds(boundsMouse, paddingLeft, paddingTop, _name);
        float accumulatedHeight=0;
        for (size_t i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            // auto& childsParent = children[i]->parent;
            if (i) {
                auto& lastChild = children[i-1];
                float width, height;
                this->getChildDimensions(lastChild, width, height);
                ofTranslate(0, height);
                name = "cd: "+child->_name;
                accumulatedHeight+=height;
                translateBounds(child->boundsMouse, 0, accumulatedHeight, name);
            }
            child->draw();
        }
        // setting the mouseBounds to the accumulated height of all children rendered
        this->boundsMouse.height = accumulatedHeight;
        ofPopMatrix();
    }
    
    void focus() {
        nodeIsFocused = true;
    }
    
    // Set the listener ID for the node
    void setListenerID(ListenerID id) {
        listenerID = id;
    }

    // Get the listener ID for the node
    ListenerID getListenerID() const {
        return listenerID;
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
