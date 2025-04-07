//
//  NfSelection.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 02.03.24.
//

#ifndef NfSelection_hpp
#define NfSelection_hpp

// Standard library includes
#include <string>
#include <vector>

// Forward declarations
namespace nfUI {
    class NfBoxxer;
    class UIEventArgs;
    class NFValue;
    class SelectionNFValue;
}

// Project includes
#include "ofMain.h"
#include "NfBoxxer.hpp"
#include "NFValue.hpp"

namespace nfUI {

class NfSelection : public NfBoxxer {
    
private:
    bool _firstRender = true;           // Flag to track if draw() was called for the first time
    bool _isDropdownOpen = false;       // Flag to track if dropdown is open
    float _dropdownHeight = 0;          // Height of the dropdown when open
    float _itemHeight = 20;             // Height of each dropdown item
    int _hoveredItem = -1;              // Index of currently hovered item (-1 for none)
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // Event declaration
    ofEvent<UIEventArgs> selectionChanged;
    
    // Member variables
    SelectionNFValue* selectionValue;    // Pointer to the selection value
    
    // Core functionality
    void draw() override;
    
    // Event handling
    bool handleRoutedMouseEvent(AppEventType type, const ofPoint& localPoint, int button) override;
    
    // Selection specific methods
    void setSelectionValue(SelectionNFValue* value);
    void updateDropdownHeight();
    void drawDropdown();
    bool isPointInDropdown(const ofPoint& point) const;
    int getItemIndexAtPoint(const ofPoint& point) const;
};

} // namespace nfUI

#endif /* NfSelection_hpp */ 