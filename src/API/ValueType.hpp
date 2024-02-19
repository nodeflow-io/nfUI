//
//  ValueType.hpp
//  nodeFlow API - the single source of truth for everything nodeFlow
//
//  Created by Matthias Strohmaier & Leonard Coster on 19.02.24.
//  based on Leonard Costers nodeFlow v1 Types
//

#ifndef ValueType_hpp
#define ValueType_hpp

#include <string>

namespace nfAPI {
enum class ValueType : uint32_t {
    NotSet = 0,
    Null,
    Bool,
    Int,
    Double,
    String,
    Timepoint,
    Duration,
    Selection,
    UUID
};

inline std::string getValueTypeString(ValueType type) {
    switch (type) {
        case ValueType::NotSet:
            return "NotSet";
            break;
        case ValueType::Null:
            return "NullType";
            break;
        case ValueType::Bool:
            return "BoolType";
            break;
        case ValueType::Int:
            return "IntType";
            break;
        case ValueType::Double:
            return "DoubleType";
            break;
        case ValueType::String:
            return "String";
            break;
        case ValueType::Timepoint:
            return "TimePoint";
            break;
        case ValueType::Duration:
            return "Duration";
            break;
        case ValueType::Selection:
            return "Selection";
            break;
        case ValueType::UUID:
            return "UUID";
            break;
        default:
            // Code for debug build
#ifdef OF_DEBUG
            assert(false && "Unknown ValueType");  // Trigger an assertion failure
#endif
            return "UnknownType: " + std::to_string(static_cast<uint32_t>(type));
            break;
    }
}

}
#endif /* ValueType_hpp */
