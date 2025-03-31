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
#include <string_view> // For std::string_view
#include <type_traits> // For std::is_base_of

#include "NfUIConfig.hpp"
#include "NFValue.hpp"
#include "NfBoxxer.hpp"

namespace nfUI {

    template<typename UIElementType, typename ValueType, typename... Args>
    [[nodiscard]] constexpr std::shared_ptr<UIElementType> createUIElement(
        const NfUIConfig& config,
        std::string_view elementName,
        Args&&... valueArgs)
    {
        static_assert(std::is_base_of<NfBoxxer, UIElementType>::value, 
                     "UIElementType must inherit from NfBoxxer");
        static_assert(std::is_base_of<NFValue, ValueType>::value, 
                     "ValueType must inherit from NFValue");
        
        // Create value first to ensure it's constructed before the UI element
        auto value = std::make_unique<ValueType>(std::forward<Args>(valueArgs)...);
        
        // Create UI element with moved value
        return std::make_shared<UIElementType>(
            config,
            std::string(elementName), // Convert string_view to string
            std::move(value)
        );
    }
}


#endif /* NfDom_hpp */
