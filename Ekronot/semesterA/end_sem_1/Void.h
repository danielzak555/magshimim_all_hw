#pragma once

#include "Type.h"

class Void : public Type{
public:
    Void() = default;
    Void(bool isTemp) : Type(isTemp) {}

    bool isPrintable() const override {
        return false;
    }

    std::string toString() const override {
        return "void";
    }
};