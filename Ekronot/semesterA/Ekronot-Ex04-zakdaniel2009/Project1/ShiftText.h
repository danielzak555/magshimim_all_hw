#pragma once
#ifndef SHIFTTEXT_H
#define SHIFTTEXT_H

#include "PlainText.h"

class ShiftText : public PlainText {
private:
    int _key;

public:
    ShiftText(std::string text, int key);

    static std::string encrypt(const std::string& text, int key);
    static std::string decrypt(const std::string& text, int key);

    std::string encrypt();
    std::string decrypt();

    friend std::ostream& operator<<(std::ostream& os, const ShiftText& st);
};

#endif
