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
    virtual ~NFValue() = default;
    virtual std::string toString() const = 0;
    virtual bool toBool() const = 0;
    virtual nfAPI::ValueType getType() const = 0;
};

class StringNFValue : public NFValue {
public:
    ofParameter<std::string> value;
    
    explicit StringNFValue(const std::string& initialValue);
    std::string toString() const override;
    nfAPI::ValueType getType() const override;
    bool toBool() const override;
};

class DoubleNFValue : public NFValue {
public:
    ofParameter<double> value;
    
    explicit DoubleNFValue(double initialValue);
    std::string toString() const override;
    nfAPI::ValueType getType() const override;
    bool toBool() const override;
};

class BoolNFValue : public NFValue {
public:
    ofParameter<bool> value;
    
    explicit BoolNFValue(bool initialValue);
    std::string toString() const override;
    nfAPI::ValueType getType() const override;
    bool toBool() const override;
};

class IntNFValue : public NFValue {
public:
    ofParameter<int> value;
    
    explicit IntNFValue(int initialValue);
    std::string toString() const override;
    nfAPI::ValueType getType() const override;
    bool toBool() const override;
};

} // namespace nfUI

#endif /* NFValue_hpp */
