//
//  NFValue.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NFValue.hpp"

namespace nfUI {

// StringNFValue implementations
StringNFValue::StringNFValue(const std::string& initialValue) : value(initialValue) {}

std::string StringNFValue::toString() const {
    return value.get();
}

nfAPI::ValueType StringNFValue::getType() const {
    return nfAPI::ValueType::String;
}

bool StringNFValue::toBool() const {
    return !value.get().empty();
}

// DoubleNFValue implementations
DoubleNFValue::DoubleNFValue(double initialValue) : value(initialValue) {}

std::string DoubleNFValue::toString() const {
    return std::to_string(value.get());
}

nfAPI::ValueType DoubleNFValue::getType() const {
    return nfAPI::ValueType::Double;
}

bool DoubleNFValue::toBool() const {
    return value.get() != 0.0;
}

// BoolNFValue implementations
BoolNFValue::BoolNFValue(bool initialValue) : value(initialValue) {}

std::string BoolNFValue::toString() const {
    return value.get() ? "1" : "0";
}

nfAPI::ValueType BoolNFValue::getType() const {
    return nfAPI::ValueType::Bool;
}

bool BoolNFValue::toBool() const {
    return value.get();
}

// IntNFValue implementations
IntNFValue::IntNFValue(int initialValue) : value(initialValue) {}

std::string IntNFValue::toString() const {
    return std::to_string(value.get());
}

nfAPI::ValueType IntNFValue::getType() const {
    return nfAPI::ValueType::Int;
}

bool IntNFValue::toBool() const {
    return value.get() != 0;
}

} // namespace nfUI
