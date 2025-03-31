//
//  NfDropdown.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 03.03.24.
//

#ifndef NfDropdown_hpp
#define NfDropdown_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"
#include "NfEventManager.hpp"

namespace nfUI {

class NfDropdown : public NfBoxxer {
public:
    NfDropdown(const NfUIConfig& config, const std::string& name);
    void selectItem(int itemIndex);
    void draw() override;
};

} // namespace nfUI

#endif /* NfDropdown_hpp */
