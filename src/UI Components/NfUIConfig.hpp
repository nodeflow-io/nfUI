//
//  NfUIConfig.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef NfUIConfig_hpp
#define NfUIConfig_hpp

#include "ofMain.h"
#include "NFConstants.h"

namespace nfUI {



struct NfUIConfig {
    ofColor backgroundColor;
    ofColor textColor;
    ofColor borderColor;
    ofColor focusColor;
    ofColor focusBackgroundColor;
    float paddingTop;
    float paddingRight;
    float paddingBottom;
    float paddingLeft;
    float marginTop;
    float marginRight;
    float marginBottom;
    float marginLeft;
    float borderSize;
    float width;
    float height;
    float minWidth;
    float minHeight;
    bool isFocused;
    ofRectangle bounds;
    uint32_t maxTextLength;
    bool textIsPassword;
    bool isAbsolutePosition;
    
    NfUIConfig() {
        // Set default values for the config
        backgroundColor = ofColor::gray;
        textColor = ofColor::white;
        borderColor = ofColor::white;
        focusColor = ofColor::yellow;
        focusBackgroundColor = ofColor::lightBlue;
        paddingTop = 5.0f;
        paddingRight = 10.0f;
        paddingBottom = 5.0f;
        paddingLeft = 10.0f;
        marginTop = 0;
        marginRight = 0;
        marginBottom = 0;
        marginLeft = 0;
        borderSize = 1.0f;
        width = 100.0f;
        height = 20.0f;
        minWidth = 50.0f;
        minHeight = 20.0f;
        isFocused = false;
        bounds = ofRectangle (0,0, 100.0f, 20.0f);
        maxTextLength = 255;
        textIsPassword = false;
        isAbsolutePosition = false;
    }
};


class Offsets {
public:
    ofParameterGroup parameters;
    ofParameter<float> top;
    ofParameter<float> right;
    ofParameter<float> bottom;
    ofParameter<float> left;
    
    Offsets(const std::string& groupName, float topValue = 0, float rightValue = 0, float bottomValue = 0, float leftValue = 0)
    : top(groupName + " Top", topValue, 0, std::numeric_limits<float>::max()),
    right(groupName + " Right", rightValue, 0, std::numeric_limits<float>::max()),
    bottom(groupName + " Bottom", bottomValue, 0, std::numeric_limits<float>::max()),
    left(groupName + " Left", leftValue, 0, std::numeric_limits<float>::max()) {
        parameters.setName(groupName);
        parameters.add(top);
        parameters.add(right);
        parameters.add(bottom);
        parameters.add(left);
    }
    
    // Getters
    float getTop() const { return top; }
    float getRight() const { return right; }
    float getBottom() const { return bottom; }
    float getLeft() const { return left; }
    
    // Setters
    void set(float value) {
        setTop(value);
        setRight(value);
        setBottom(value);
        setLeft(value);
    }
    void setTop(float value) { top = std::min(value, std::numeric_limits<float>::max()); }
    void setRight(float value) { right = std::min(value, std::numeric_limits<float>::max()); }
    void setBottom(float value) { bottom = std::min(value, std::numeric_limits<float>::max()); }
    void setLeft(float value) { left = std::min(value, std::numeric_limits<float>::max()); }
};

} // nfUI

#endif /* NfUIConfig_hpp */
