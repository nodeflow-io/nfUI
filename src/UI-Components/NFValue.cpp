//
//  NFValue.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NFValue.hpp"
#include "ofLog.h" // Added for logging

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

// SelectionNFValue implementations
const std::string SelectionNFValue::NOTHING_SELECTED_NAME = "NOTHING SELECTED";

SelectionNFValue::SelectionNFValue(std::vector<std::string> _names, std::vector<int> _values, int initialIndex)
    : names(std::move(_names)), values(std::move(_values)) {

    if (names.size() != values.size()) {
        ofLogError("SelectionNFValue") << "Cannot construct with different sized name and value vectors. Initializing empty.";
        names.clear();
        values.clear();
        index.setWithoutEventNotifications(-1);
        index.setName("selectionIndex"); // Give the parameter a name
        return;
    }

    if ((initialIndex < 0 || initialIndex >= values.size()) && initialIndex != -1) {
        ofLogWarning("SelectionNFValue") << "Cannot construct with invalid selected index " << initialIndex << ". Defaulting to -1.";
        index.setWithoutEventNotifications(-1);
    } else {
        index.setWithoutEventNotifications(initialIndex);
    }
    index.setName("selectionIndex"); // Give the parameter a name
}

std::string SelectionNFValue::toString() const {
    return getSelectedName();
}

nfAPI::ValueType SelectionNFValue::getType() const {
    return nfAPI::ValueType::Selection;
}

bool SelectionNFValue::toBool() const {
    return index.get() != -1;
}

bool SelectionNFValue::setIndex(int _index) {
    if ((_index < 0 || _index >= values.size()) && _index != -1) {
        ofLogError("SelectionNFValue") << "setIndex requested index " << _index << " is out of range.";
        // Optionally set to -1 or keep current? Let's keep current for now.
        return false;
    }
    index.set(_index);
    return true;
}

int SelectionNFValue::getIndex() const {
    return index.get();
}

std::string SelectionNFValue::getSelectedName() const {
    int currentIndex = index.get();
    if (currentIndex == -1 || currentIndex >= names.size()) { // Added size check for safety
        return NOTHING_SELECTED_NAME;
    }
    return names[currentIndex];
}

int SelectionNFValue::getSelectedValue() const {
    int currentIndex = index.get();
    if (currentIndex == -1 || currentIndex >= values.size()) { // Added size check for safety
        return 0; // Assuming a default value for not selected
    }
    return values[currentIndex];
}

const std::vector<std::string>& SelectionNFValue::getNamesList() const {
    return names;
}

const std::vector<int>& SelectionNFValue::getValuesList() const {
    return values;
}

} // namespace nfUI
