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

    // Constructor
    NfBoxxer(const NfUIConfig& config, const std::string& name, std::unique_ptr<NFValue> initialValue);
    
    // Core functionality
    void draw();
    void drawChildren(const float& paddingLeft, const float& paddingTop);
    void focus();
    
    // Listener management
    void setListenerID(ListenerID id);
    ListenerID getListenerID() const;
};

} // nfUI

#endif /* NfBoxxer_hpp */
