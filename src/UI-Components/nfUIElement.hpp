//
//  nfUIElement.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef nfUIElement_hpp
#define nfUIElement_hpp

#include "ofMain.h"
#include "NfUIConfig.hpp"
#include "../API/ValueType.hpp"
#include "NFValue.hpp"
#include "NfEventManager.hpp"

namespace nfUI {

// TODO: break this out into its own header
class UIEventArgs : public ofEventArgs {
public:
    UIEventArgs() = default;
};

class NfUIElement : public std::enable_shared_from_this<NfUIElement> {
    
private:
    std::unique_ptr<NFValue> value; // Smart pointer to NFValue
    bool _dimensionsDirty = true;    // Flag to track if dimensions need recalculation
    float _cachedWidth = 0.0f;       // Cached width value
    float _cachedHeight = 0.0f;      // Cached height value

public:
    std::weak_ptr<NfUIElement> parent; // Weak pointer to the parent element
    std::vector<std::shared_ptr<NfUIElement>> children; // List of children elements
    NfUIConfig _config; // Hold configuration settings for this UI element
    std::string _name;
    nfAPI::ValueType valueType;
    ofParameterGroup parameters;
    ofParameter<ofColor> backgroundColor;
    ofParameter<ofColor> textColor;
    ofParameter<ofColor> borderColor;
    ofParameter<ofColor> focusColor;
    ofParameter<ofColor> focusBackgroundColor;
    Offsets padding;
    Offsets margin;
    ofParameter<float> borderSize;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> minWidth;
    ofParameter<float> minHeight;
    ofParameter<float> maxWidth;
    ofParameter<float> maxHeight;
    ofParameter<bool> isFocused;
    ofParameter<bool> isVisible;
    std::string text;
    ofParameter<uint32_t> maxTextLength;
    ofParameter<bool> textIsPassword;
    ofParameter<bool> isAbsolutePosition;
    
    ofRectangle bounds;
    ofRectangle boundsMouse;

    // Constructor
    NfUIElement(const NfUIConfig& config = NfUIConfig(), 
                std::unique_ptr<NFValue> initialValue = nullptr, 
                const std::string& elementName = "DefaultName");

    // Core functionality
    virtual void draw() = 0;
    bool isRoot() const;
    NfUIElement* findRoot();
    void addChild(const std::shared_ptr<NfUIElement>& child);
    void setValue(std::unique_ptr<NFValue> newValue);
    NFValue* getValue() const;
    void markDimensionsDirty();
    
    // Dimension and position management
    void getDimensions(float& width, float& height);
    void getPosition(ofPoint& position);
    void setPosition(const ofPoint& position);
    void getChildDimensions(const std::shared_ptr<NfUIElement>& child, float& width, float& height);
    void translateBounds(ofRectangle& boundsref, float deltaX, float deltaY, std::string name = "");
    size_t getChildCountOfRoot();
};

} // namespace nfUI

#endif /* nfUIElement_hpp */
