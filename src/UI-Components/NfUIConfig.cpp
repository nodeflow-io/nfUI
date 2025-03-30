//
//  NfUIConfig.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NfUIConfig.hpp"

namespace nfUI {

// NfUIConfig implementations
NfUIConfig::NfUIConfig() {
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
    contentWidth = 0;
    contentHeight = 0;
    minWidth = 0;
    minHeight = 0;
    isFocused = false;
    bounds = ofRectangle(0, 0, 100.0f, 20.0f);
    maxTextLength = 255;
    textIsPassword = false;
    isAbsolutePosition = false;
    isDebug = false;
    showLabel = false;
}

void NfUIConfig::setMargin(float top, float right, float bottom, float left) {
    marginTop = top;
    marginRight = right;
    marginBottom = bottom;
    marginLeft = left;
}

void NfUIConfig::setMargin(float margin) {
    marginTop = margin;
    marginRight = margin;
    marginBottom = margin;
    marginLeft = margin;
}

void NfUIConfig::setPadding(float top, float right, float bottom, float left) {
    paddingTop = top;
    paddingRight = right;
    paddingBottom = bottom;
    paddingLeft = left;
}

void NfUIConfig::setPadding(float padding) {
    paddingTop = padding;
    paddingRight = padding;
    paddingBottom = padding;
    paddingLeft = padding;
}

// Offsets implementations
Offsets::Offsets(const std::string& groupName, float topValue, float rightValue, float bottomValue, float leftValue)
    : top(groupName + " Top", topValue, 0, std::numeric_limits<float>::max())
    , right(groupName + " Right", rightValue, 0, std::numeric_limits<float>::max())
    , bottom(groupName + " Bottom", bottomValue, 0, std::numeric_limits<float>::max())
    , left(groupName + " Left", leftValue, 0, std::numeric_limits<float>::max())
{
    parameters.setName(groupName);
    parameters.add(top);
    parameters.add(right);
    parameters.add(bottom);
    parameters.add(left);
}

// Offsets getters
float Offsets::getTop() const { return top; }
float Offsets::getRight() const { return right; }
float Offsets::getBottom() const { return bottom; }
float Offsets::getLeft() const { return left; }

// Offsets setters
void Offsets::set(float value) {
    setTop(value);
    setRight(value);
    setBottom(value);
    setLeft(value);
}

void Offsets::setTop(float value) { top = std::min(value, std::numeric_limits<float>::max()); }
void Offsets::setRight(float value) { right = std::min(value, std::numeric_limits<float>::max()); }
void Offsets::setBottom(float value) { bottom = std::min(value, std::numeric_limits<float>::max()); }
void Offsets::setLeft(float value) { left = std::min(value, std::numeric_limits<float>::max()); }

} // namespace nfUI
