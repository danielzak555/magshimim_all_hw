#pragma once

#include "Type.h"

class String : public Type{
    public:
        String() = default;
        String(const std::string& value, bool isTemp) : Type(isTemp), _value(value) {}

        const std::string& getValue() const { return _value; }
        void setValue(const std::string& value) { _value = value; }

        bool isPrintable() const override { return true; }
        std::string toString() const override { return _value; }

    private:
        std::string _value;
};