#pragma once
#ifndef CAESARTEXT_H
#define CAESARTEXT_H

#include "ShiftText.h"

class CaesarText : public ShiftText {

public:
    CaesarText(std::string text);

    static std::string encrypt(const std::string& text);
    static std::string decrypt(const std::string& text);

    std::string encrypt();
    std::string decrypt();
    friend std::ostream& operator<<(std::ostream& os, const CaesarText& ct);
};

#endif
