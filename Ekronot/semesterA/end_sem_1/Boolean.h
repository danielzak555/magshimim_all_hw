#pragma once

#include "Type.h"

class Boolean : public Type{
    private:
        bool _value;

    public:
        Boolean() : Type(false), _value(false) {}
        Boolean(bool value, bool isTemp) : Type(isTemp), _value(value) {}

        bool getValue() const { return _value; }
        void setValue(bool value) { _value = value; }

        bool isPrintable() const override { return true; }
        std::string toString() const override { return _value ? "true" : "false"; }
};