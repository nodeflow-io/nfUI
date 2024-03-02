//
//  NfDom.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 22.02.24.
//

#ifndef NfDom_hpp
#define NfDom_hpp

#include <memory> // For std::shared_ptr and std::unique_ptr
#include <string> // For std::string

#include "NfUIConfig.hpp"
#include "NFValue.hpp"

namespace nfUI {

    // TODO: investigate why this does not work with st::make_shared
    // it would be more performant and we are on c++17
    template<typename UIElementType, typename ValueType, typename... Args>
    std::shared_ptr<UIElementType> createUIElement(
        const NfUIConfig& config,
        const std::string& elementName,
        Args&&... valueArgs)
    {
        // Construct the ValueType object with the provided arguments
        auto value = std::make_unique<ValueType>(std::forward<Args>(valueArgs)...);

        // Construct the UI element with the config, name, and ValueType object
        return std::make_shared<UIElementType>(
            config,
            elementName,
            std::move(value) // Move the unique_ptr to the constructor
        );
    }
}


#endif /* NfDom_hpp */
