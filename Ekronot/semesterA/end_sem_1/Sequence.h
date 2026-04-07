#pragma once

#include "Type.h"
class Sequence : public Type
{
    public:
        Sequence() = default;

        bool isPrintable() const override { return true; }
        std::string toString() const override { return "Sequence"; }
};