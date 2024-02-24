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
            std::cout << "Boxxer: First render of " << _name << std::endl;
            NFValue* valueRawPtr = this->getValue();
            if (valueRawPtr != nullptr) {
                std::string valueAsString = valueRawPtr->toString();
                std::cout << "Boxxer: Value as string: " << valueAsString << std::endl;
            } else {
                std::cout << "Boxxer: No value available." << std::endl;
            }
        }
        // this is used for keeping track of the bounds for mouse interactions
        // we only do this if our element is the parent element
        if (this->isRoot()) {
            this->boundsMouse=bounds;
        }
        
        // decide wheter we need to translate to an absolute position
        if (_config.isAbsolutePosition) {
            ofTranslate(bounds.x, bounds.y);
            translateBounds(boundsMouse, bounds.x, bounds.y);
        }
        
        // decide wheter we need to translate to an absolute position
        if (_config.marginTop || _config.marginLeft) {
            ofTranslate(_config.marginLeft, _config.marginTop);
            translateBounds(boundsMouse, _config.marginLeft, _config.marginTop);
        }
        
        // TODO: remove this
        std::cout << "Boxxer: " << _name << " mB: " << boundsMouse.x << " " << boundsMouse.y << std::endl;
        // After the first render, set the flag to false
        if (_firstRender) {
            _firstRender = false;
        }
    }

    
    void drawChildren (const float& paddingLeft, const float& paddingRight) {
        ofPushMatrix();
        ofTranslate(paddingLeft, paddingRight);
        translateBounds(boundsMouse, paddingLeft, paddingRight);
        for (size_t i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            if (i) {
                auto& lastChild = children[i-1];
                float width, height;
                this->getChildDimensions(lastChild, width, height);
                ofTranslate(0, height);
                translateBounds(boundsMouse, 0, height);
            }
            child->draw();
        }
        ofPopMatrix();
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
