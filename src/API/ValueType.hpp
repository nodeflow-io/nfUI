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
#include <algorithm>

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

// Function declarations
std::string getValueTypeString(ValueType type);
bool toBool(const std::string& str);
int toInt(const std::string& str);
double toDouble(const std::string& str);

} // namespace nfAPI

#endif /* ValueType_hpp */


