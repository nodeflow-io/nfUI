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
    float width, height; // Dimensions of the box
    
    NfBoxxer(float w, float h) : width(w), height(h) {}
    
    void draw() override {
        // Generate a random color
        ofColor randomColor = ofColor::fromHsb(ofRandom(255), 255, 255);

        // Set the color for drawing
        ofSetColor(randomColor);
        ofDrawRectangle(0, 0, width, height); // Draw a rectangle representing the box
    }
};

} // nfUI
#endif /* NfBoxxer_hpp */
