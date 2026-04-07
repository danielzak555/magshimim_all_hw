#pragma once
#ifndef SUBSTITUTIONTEXT_H
#define SUBSTITUTIONTEXT_H

#include "PlainText.h"
#include <string>

class SubstitutionText : public PlainText {
private:
    std::string _dictionaryFileName;

public:
    SubstitutionText(std::string text, std::string dictionaryFileName);

    static std::string encrypt(std::string text, std::string dictionaryFileName);
    static std::string decrypt(std::string text, std::string dictionaryFileName);

    std::string encrypt();
    std::string decrypt();

	friend std::ostream& operator<<(std::ostream& os, const SubstitutionText& st);
};

#endif
