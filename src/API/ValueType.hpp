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
        case ValueType::Null:
            return "NullType";
        case ValueType::Bool:
            return "BoolType";
        case ValueType::Int:
            return "IntType";
        case ValueType::Double:
            return "DoubleType";
        case ValueType::String:
            return "String";
        case ValueType::Timepoint:
            return "TimePoint";
        case ValueType::Duration:
            return "Duration";
        case ValueType::Selection:
            return "SelectionType";
        case ValueType::UUID:
            return "UUID";
        default:
            return "UnknownType: " + std::to_string(static_cast<uint32_t>(type));
    }
}

}
#endif /* ValueType_hpp */
