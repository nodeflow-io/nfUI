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
#include <cstdint> // For uint32_t
#include <iostream>

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
            return "Null";
        case ValueType::Bool:
            return "Bool";
        case ValueType::Int:
            return "IntT";
        case ValueType::Double:
            return "Double";
        case ValueType::String:
            return "String";
        case ValueType::Timepoint:
            return "Timepoint";
        case ValueType::Duration:
            return "Duration";
        case ValueType::Selection:
            return "Selection";
        case ValueType::UUID:
            return "UUID";
        default:
            return "UnknownType: " + std::to_string(static_cast<uint32_t>(type));
    }
}

// TODO : Put this in its own file ???

inline bool toBool(const std::string& str) {
    std::string output = str;
    std::transform(output.begin(), output.end(), output.begin(),
                       [](unsigned char c) { return std::tolower(c); });
    return output == "true" || output == "1";
}

// This class ValueTypeHandler demonstrates the usage of ValueType
// should be added to API Examples
// this is useful for debugging because you can set it to show you the address of your objects

class ValueTypeHandler {
private:
    ValueType _currentType;
    bool _showDebugInfos;

public:
    ValueTypeHandler(bool showDebugInfos = false) :
        _showDebugInfos(showDebugInfos),
        _currentType(ValueType::NotSet) {
        if(_showDebugInfos) {
            std::cout << "ValueTypeHandler() @" << this << " = NotSet" << std::endl;
        }
    }

    void setValueType(ValueType newType) {
        _currentType = newType;
        if(_showDebugInfos) {
            std::cout << "ValueTypeHandler::setValueType @" << this << " (" << getValueTypeString(newType) << ")" << std::endl;
        }
    }

    ValueType getValueType() const {
        if(_showDebugInfos) {
            std::cout << "ValueTypeHandler::getValueType @" << this << " (" << getValueTypeString(_currentType) << ")" << std::endl;
        }
        return _currentType;
    }

    std::string getValueTypeString() const {
        return getValueTypeString(_currentType);
    }

    std::string getValueTypeString(const ValueType& type) const {
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
                return "Selection";
            case ValueType::UUID:
                return "UUID";
            default:
#ifdef OF_DEBUG
                assert(false && "Unknown ValueType");
#endif
                return "UnknownType: " + std::to_string(static_cast<uint32_t>(type));
        }
    }
};

} // namespace nfAPI

#endif /* ValueType_hpp */

/* USAGE
 
 #include <iostream>

 // Assume ValueType and ValueTypeHandler are defined in the nfAPI namespace as shown previously

 int main() {
     nfAPI::ValueTypeHandler typeHandler;

     // Setting the ValueType to IntType
     typeHandler.setValueType(nfAPI::ValueType::Int);

     // Getting and printing the current ValueType as a string
     std::cout << "Current ValueType: " << typeHandler.getValueTypeString() << std::endl;

     // Changing the ValueType to StringType
     typeHandler.setValueType(nfAPI::ValueType::String);

     // Getting and printing the new ValueType as a string
     std::cout << "New ValueType: " << typeHandler.getValueTypeString() << std::endl;

     return 0;
 }
 
 
 */
