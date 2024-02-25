//
//  NfBoxxer.hpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 21.02.24.
//

#ifndef NfBoxxer_hpp
#define NfBoxxer_hpp

#include "nfUIElement.hpp"
namespace nfUI {

class NfBoxxer : public NfUIElement {
    
private:
    bool _firstRender = true; // Flag to track if draw() was called for the first time

public:
    std::string _name;
    NfUIConfig _config; // Reference to a NfUIConfig object


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
            this->boundsMouse=bounds;
            for (size_t i = 0; i < children.size(); ++i) {
                auto& child = children[i];
                child->boundsMouse=child->bounds;
            }
        }
        
        // decide wheter we need to translate to an absolute position
        if (_config.isAbsolutePosition) {
            ofTranslate(bounds.x, bounds.y);
            translateBounds(boundsMouse, bounds.x, bounds.y, _name);
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
        float accumulatedHeight;
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
        ofPopMatrix();
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
