#include "ShiftText.h"

ShiftText::ShiftText(std::string text, int key)
    : PlainText(text)
{
    _key = key;
    _text = encrypt(text, key);
    isEnc = true;
}

std::string ShiftText::encrypt(const std::string& text, int key) {
    std::string result = text;

    for (int i = 0; i < (int)result.length(); i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = 'a' + ((result[i] - 'a' + key) % 26);
        }
    }
    return result;
}

std::string ShiftText::decrypt(const std::string& text, int key) {
    std::string result = text;

    for (int i = 0; i < (int)result.length(); i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = 'a' + ((result[i] - 'a' - key + 26) % 26);
        }
    }
    return result;
}

std::string ShiftText::encrypt() {
    if (!isEnc) {
        _text = encrypt(_text, _key);
        isEnc = true;
    }
    return _text;
}

std::string ShiftText::decrypt() {
    if (isEnc) {
        _text = decrypt(_text, _key);
        isEnc = false;
    }
    return _text;
}

std::ostream& operator<<(std::ostream& os, const ShiftText& st) {
    os << "ShiftText " << st._text;
    return os;
}
