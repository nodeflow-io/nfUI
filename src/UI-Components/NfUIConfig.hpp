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
    float contentWidth;
    float contentHeight;
    bool isFocused;
    ofRectangle bounds;
    uint32_t maxTextLength;
    bool textIsPassword;
    bool isAbsolutePosition;
    bool isDebug;
    bool showLabel;
    
    NfUIConfig();
    void setMargin(float top, float right, float bottom, float left);
    void setMargin(float margin);
    void setPadding(float top, float right, float bottom, float left);
    void setPadding(float padding);
};

class Offsets {
public:
    ofParameterGroup parameters;
    ofParameter<float> top;
    ofParameter<float> right;
    ofParameter<float> bottom;
    ofParameter<float> left;
    
    Offsets(const std::string& groupName, float topValue = 0, float rightValue = 0, float bottomValue = 0, float leftValue = 0);
    
    // Getters
    float getTop() const;
    float getRight() const;
    float getBottom() const;
    float getLeft() const;
    
    // Setters
    void set(float value);
    void setTop(float value);
    void setRight(float value);
    void setBottom(float value);
    void setLeft(float value);
};

} // namespace nfUI

#endif /* NfUIConfig_hpp */
