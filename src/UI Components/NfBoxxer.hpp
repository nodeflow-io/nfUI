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
public:
    float _width, _height; // Dimensions of the box
    std::string _name;
    NfBoxxer(float w, float h, std::string name) :
    _width(w),
    _height(h),
    _name(name)
    {}
    
    void draw() override {
        // Generate a random color
        ofColor randomColor = ofColor(_height,0,0); // ofColor::fromHsb(ofRandom(255), 255, 255);

        // std::cout << _name << ": " << _width << "," << _height << std::endl;

        // Set the color for drawing
        ofSetColor(randomColor);
        ofDrawRectangle(0, 0, _width, _height); // Draw a rectangle representing the box
        for (auto& child : children) {
            child->draw(); // Recursively draw each child
        }
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
