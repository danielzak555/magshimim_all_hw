#pragma once
#include "InterpreterException.h"
#include <string>

class NameErrorException : public InterpreterException
{
private:
    std::string msg;

public:
    explicit NameErrorException(const std::string& message) : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};
