#include "PlainText.h"

int PlainText::numOfTexts = 0;

PlainText::PlainText(const std::string& text) {
    _text = text;
    isEnc = false;
    numOfTexts++;
}

bool PlainText::isEncrypted() const{
    return isEnc;
}

std::string PlainText::getText() const{
    return _text;
}

std::ostream& operator<<(std::ostream& os, const PlainText& pt) {
    os << "PlainText: " << pt.getText();
    return os;
}
