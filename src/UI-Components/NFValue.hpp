//
//  NFValue.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 21.02.24.
//

#ifndef NFValue_hpp
#define NFValue_hpp

#include "ofMain.h"
#include "../API/ValueType.hpp"

namespace nfUI {

class NFValue {
public:
    virtual ~NFValue() {}
    
    virtual std::string toString() const = 0;
    virtual bool toBool() const = 0;
    virtual nfAPI::ValueType getType() const = 0;
};

class StringNFValue : public NFValue {
public:
    ofParameter<std::string> value;
    
    StringNFValue(const std::string& initialValue) : value(initialValue) {}
    
    std::string toString() const override {
        return value.get();
    }
    
    nfAPI::ValueType getType() const override {
        return nfAPI::ValueType::String;
    }
    
    bool toBool() const override {
        return !value.get().empty();
    }
};

class DoubleNFValue : public NFValue {
public:
    ofParameter<double> value;
    
    DoubleNFValue(double initialValue) : value(initialValue) {}
    
    std::string toString() const override {
        return std::to_string(value.get());
    }
    
    nfAPI::ValueType getType() const override {
        return nfAPI::ValueType::Double;
    }
    
    bool toBool() const override {
        return value.get() != 0.0;
    }
};

class BoolNFValue : public NFValue {
public:
    ofParameter<bool> value;
    
    BoolNFValue(bool initialValue) : value(initialValue) {}
    
    std::string toString() const override {
        return value.get() ? "1" : "0";
    }
    
    nfAPI::ValueType getType() const override {
        return nfAPI::ValueType::Bool;
    }
    
    bool toBool() const override {
        return value.get();
    }
};

class IntNFValue : public NFValue {
public:
    ofParameter<int> value;
    
    IntNFValue(int initialValue) : value(initialValue) {}
    
    std::string toString() const override {
        return std::to_string(value.get());
    }
    
    nfAPI::ValueType getType() const override {
        return nfAPI::ValueType::Int;
    }
    
    bool toBool() const override {
        return value.get() != 0;
    }
};

}
#endif /* NFValue_hpp */
