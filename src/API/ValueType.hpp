//
//  ValueType.hpp
//  nodeFlow
//
//  Created by Matthias Strohmaier on 19.02.24.
//  based on Leonard Costers nodeFlow-Types
//

#ifndef ValueType_hpp
#define ValueType_hpp

#include <string>

namespace nfAPI {
enum class ValueType : uint32_t {
    NotSet = 0,
    NullType,
    BoolType,
    IntType,
    DoubleType,
    StringType,
    TimePointType,
    DurationType,
    SelectionType,
    UIDType
};

inline std::string getValueTypeString(ValueType type) {
    switch (type) {
        case ValueType::NotSet:
            return "NotSet";
        case ValueType::NullType:
            return "NullType";
        case ValueType::BoolType:
            return "BoolType";
        case ValueType::IntType:
            return "IntType";
        case ValueType::DoubleType:
            return "DoubleType";
        case ValueType::StringType:
            return "StringType";
        case ValueType::TimePointType:
            return "TimePointType";
        case ValueType::DurationType:
            return "DurationType";
        case ValueType::SelectionType:
            return "SelectionType";
        case ValueType::UIDType:
            return "UIDType";
        default:
            return "UnknownType: " + std::to_string(static_cast<uint32_t>(type));
    }
}

}
#endif /* ValueType_hpp */
