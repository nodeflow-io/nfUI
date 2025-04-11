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
    bool _transformationDirty = true; // Flag to track if bounds need recalculation
    bool _childrenTransformationDirty = true; // Flag to track if children bounds need recalculation
    ListenerID listenerID;
    
public:
    static bool showDebugBounds; // Global flag to toggle bounds visualization
    
    std::string _name;
    NfUIConfig _config;
    bool nodeIsFocused = false;

    // Constructor
    NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue);
    
    // Core functionality
    void draw();
    void drawChildren(const float& paddingLeft, const float& paddingTop);
    void focus();
    
    // Override update method from NfUIElement
    void update() override;
    void updateChildren();
    
    // Position and size management
    void setPosition(const ofPoint& position);
    void setSize(float width, float height);
    
    // Bounds transformation methods
    void updateGlobalBounds();
    void updateChildrenBounds();
    void markTransformationDirty(bool includeChildren = true);
    
    // Debug visualization
    void drawMouseBounds();
    void drawChildrenMouseBounds();
    
    // Floating element support
    virtual bool hasFloatingElement() const { return false; }
    virtual bool isPointInFloatingElement(const ofPoint& globalPoint) const { return false; }
    virtual bool handleFloatingElementEvent(AppEventType type, const ofPoint& globalPoint, int button) { return false; }
    
    // Route events to handle floating elements
    bool routeEventToFloatingElements(AppEventType type, const ofPoint& globalPoint, int button);
    
    // Listener management
    void setListenerID(ListenerID id);
    ListenerID getListenerID() const;
};

} // nfUI

#endif /* NfBoxxer_hpp */
