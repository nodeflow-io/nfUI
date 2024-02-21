//
//  NFValue.hpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 21.02.24.
//

#ifndef NFValue_hpp
#define NFValue_hpp

#include "ofMain.h"

namespace nfUI {

class NFValue {
public:
    virtual ~NFValue() {}

    // Virtual function to return value as string
    virtual std::string toString() const = 0;
};

// Example NFValues using ofParameter types
class StringNFValue : public NFValue {
public:
    ofParameter<std::string> value;

    StringNFValue(const std::string& initialValue) : value(initialValue) {}

    std::string toString() const override {
        return value.get();
    }
};


class DoubleNFValue : public NFValue {
public:
    ofParameter<double> value;

    DoubleNFValue(double initialValue) : value(initialValue) {}

    std::string toString() const override {
        return std::to_string(value.get());
    }
};

class BoolNFValue : public NFValue {
public:
    ofParameter<bool> value;

    BoolNFValue(bool initialValue) : value(initialValue) {}

    std::string toString() const override {
        return value.get() ? "true" : "false";
    }
};

class IntNFValue : public NFValue {
public:
    ofParameter<int> value;

    IntNFValue(int initialValue) : value(initialValue) {}

    std::string toString() const override {
        return std::to_string(value.get());
    }
};

}
#endif /* NFValue_hpp */
