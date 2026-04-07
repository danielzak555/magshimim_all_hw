#pragma once

#include "Type.h"

class Integer : public Type
{
    public:
        Integer() = default;
        Integer(int value, bool isTemp) : Type(isTemp), _value(value) {}

        int getValue() const { return _value; }
        void setValue(int value) { _value = value; }

        bool isPrintable() const override { return true; }
        std::string toString() const override { return std::to_string(_value); }

    private:
        int _value;
};