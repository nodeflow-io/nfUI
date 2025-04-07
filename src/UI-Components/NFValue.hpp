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
#include <vector>

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

class SelectionNFValue : public NFValue {
public:
    static const int NOTHING_SELECTED_INDEX = -1;
    static const std::string NOTHING_SELECTED_NAME;
    static const int NOTHING_SELECTED_VALUE = 0;

    ofParameter<int> index;
    std::vector<std::string> names;
    std::vector<int> values;

    explicit SelectionNFValue(std::vector<std::string> _names, std::vector<int> _values, int initialIndex = NOTHING_SELECTED_INDEX);

    // NFValue overrides
    std::string toString() const override;
    nfAPI::ValueType getType() const override;
    bool toBool() const override;

    // Selection specific methods
    bool setIndex(int _index);
    int getIndex() const;
    std::string getSelectedName() const;
    int getSelectedValue() const;
    const std::vector<std::string>& getNamesList() const;
    const std::vector<int>& getValuesList() const;
};

} // namespace nfUI

#endif /* NFValue_hpp */
