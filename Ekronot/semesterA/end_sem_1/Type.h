#pragma once

#include <stdbool.h>
#include <string>

class Type
{   
    private:
        bool _isTemp;

    public:
        Type() = default;
        Type(bool isTemp) : _isTemp(isTemp) {}

        bool isTemp() const { return _isTemp; }
        void setTemp(bool isTemp) { _isTemp = isTemp; }

        virtual ~Type() = default;
        virtual bool isPrintable() const = 0;
        virtual std::string toString() const = 0;
};
