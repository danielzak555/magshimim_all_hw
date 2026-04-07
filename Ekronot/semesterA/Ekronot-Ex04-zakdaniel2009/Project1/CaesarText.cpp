#include "CaesarText.h"

CaesarText::CaesarText(std::string text)
    : ShiftText(text, 3) {
}
    
std::string CaesarText::encrypt(const std::string& text) {
	return ShiftText::encrypt(text, 3);
}
std::string CaesarText::decrypt(const std::string& text) {
	return ShiftText::decrypt(text, 3);
}

std::string CaesarText::encrypt() {
    return ShiftText::encrypt();
}

std::string CaesarText::decrypt() {
    return ShiftText::decrypt();
}

std::ostream& operator<<(std::ostream& os, const CaesarText& ct) {
    os << "CaesarText: " << ct.getText();
    return os;
}
