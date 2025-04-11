//
//  NFValue.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#include "NFValue.hpp"
#include "ofLog.h" // Added for logging

// Set to 0 to disable all SelectionNFValue debug output
#define DEBUG_SELECTION_VALUE 1

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
    : names(_names), values(_values) {

#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "Constructor: names.size()=" << names.size() 
        << ", values.size()=" << values.size() << ", initialIndex=" << initialIndex;
#endif

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
    
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "Constructor complete: index=" << index.get();
#endif
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
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "setIndex: requested=" << _index 
        << ", values.size()=" << values.size();
#endif

    if ((_index < 0 || _index >= values.size()) && _index != -1) {
        ofLogError("SelectionNFValue") << "setIndex requested index " << _index << " is out of range.";
        // Optionally set to -1 or keep current? Let's keep current for now.
        return false;
    }
    index.set(_index);
    
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "setIndex: new index=" << index.get();
#endif
    return true;
}

int SelectionNFValue::getIndex() const {
    int result = index.get();
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getIndex: returning " << result;
#endif
    return result;
}

std::string SelectionNFValue::getSelectedName() const {
    int currentIndex = index.get();
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getSelectedName: currentIndex=" << currentIndex 
        << ", names.size()=" << names.size() << ", names.empty()=" << names.empty();
#endif

    // Check if index is invalid, names is empty, or index is out of bounds
    if (currentIndex == -1 || names.empty() || currentIndex >= names.size()) {
#if DEBUG_SELECTION_VALUE
        ofLogNotice("SelectionNFValue") << "getSelectedName: returning NOTHING_SELECTED_NAME";
#endif
        return NOTHING_SELECTED_NAME;
    }
    
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getSelectedName: returning '" << names[currentIndex] << "'";
#endif
    return names[currentIndex];
}

int SelectionNFValue::getSelectedValue() const {
    int currentIndex = index.get();
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getSelectedValue: currentIndex=" << currentIndex 
        << ", values.size()=" << values.size() << ", values.empty()=" << values.empty()
        << ", this=" << (void*)this;
#endif

    // Check if index is invalid, values is empty, or index is out of bounds
    if (currentIndex == -1 || values.empty() || currentIndex >= values.size()) {
#if DEBUG_SELECTION_VALUE
        ofLogNotice("SelectionNFValue") << "getSelectedValue: returning NOTHING_SELECTED_VALUE";
#endif
        return NOTHING_SELECTED_VALUE;
    }
    
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getSelectedValue: returning " << values[currentIndex];
#endif
    return values[currentIndex];
}

const std::vector<std::string>& SelectionNFValue::getNamesList() const {
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getNamesList: size=" << names.size();
#endif
    return names;
}

const std::vector<int>& SelectionNFValue::getValuesList() const {
#if DEBUG_SELECTION_VALUE
    ofLogNotice("SelectionNFValue") << "getValuesList: size=" << values.size();
#endif
    return values;
}

} // namespace nfUI
