//
//  ValueType.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 19.02.24.
//

#include "ValueType.hpp"

namespace nfAPI {

std::string getValueTypeString(ValueType type) {
    switch (type) {
        case ValueType::NotSet:
            return "NotSet";
        case ValueType::Null:
            return "Null";
        case ValueType::Bool:
            return "Bool";
        case ValueType::Int:
            return "Int";
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

bool toBool(const std::string& str) {
    std::string output = str;
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return output == "true" || output == "1";
}

int toInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        // Handle or log the error as needed
        return 0; // Return a default value
    } catch (const std::out_of_range& e) {
        // Handle or log the error as needed
        return 0; // Return a default value
    }
}

double toDouble(const std::string& str) {
    try {
        return std::stod(str);
    } catch (const std::invalid_argument& e) {
        // Handle or log the error as needed
        return 0.0; // Return a default value
    } catch (const std::out_of_range& e) {
        // Handle or log the error as needed
        return 0.0; // Return a default value
    }
}

} // namespace nfAPI
