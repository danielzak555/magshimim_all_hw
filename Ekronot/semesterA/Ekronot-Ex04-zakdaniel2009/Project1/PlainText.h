#pragma once
#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <string>
#include <iostream>

class PlainText {
protected:
    std::string _text;
    bool isEnc;

public:
    static int numOfTexts;
    PlainText(const std::string& text);
    bool isEncrypted() const;
    std::string getText() const;
    friend std::ostream& operator<<(std::ostream& os, const PlainText& pt);
};

#endif
