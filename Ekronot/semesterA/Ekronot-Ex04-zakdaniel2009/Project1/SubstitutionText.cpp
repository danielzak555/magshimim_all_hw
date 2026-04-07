#include "SubstitutionText.h"
#include <fstream>

void loadDictionary(const std::string& fileName, char map[26])
{
    std::ifstream file(fileName);
    char plain, cipher;

    for (int i = 0; i < 26; i++)
        map[i] = 'a' + i;

    if (!file.is_open())
        return;

    while (file >> plain)
    {
        file.get();
        file >> cipher;
        if (plain >= 'a' && plain <= 'z')
        {
            int index = plain - 'a';
            map[index] = cipher;
        }
    }

    file.close();
}

SubstitutionText::SubstitutionText(std::string text, std::string dictionaryFileName)
    : PlainText(text), _dictionaryFileName(dictionaryFileName)
{
    _text = encrypt(text, dictionaryFileName);
    isEnc = true;
}

std::string SubstitutionText::encrypt(std::string text, std::string dictionaryFileName)
{
    char map[26];
    for (int i = 0; i < 26; i++)
        map[i] = ' ';

    loadDictionary(dictionaryFileName, map);

    for (int i = 0; i < (int)text.length(); i++)
    {
        char c = text[i];
        if (c >= 'a' && c <= 'z')
        {
            int index = c - 'a';
            text[i] = map[index];
        }
    }

    return text;
}

std::string SubstitutionText::decrypt(std::string text, std::string dictionaryFileName)
{
    char map[26];
    for (int i = 0; i < 26; i++)
        map[i] = ' ';

    loadDictionary(dictionaryFileName, map);

    for (int i = 0; i < (int)text.length(); i++)
    {
        char c = text[i];
        if (c >= 'a' && c <= 'z')
        {
            for (int j = 0; j < 26; j++)
            {
                if (map[j] == c)
                {
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }

    return text;
}

std::string SubstitutionText::encrypt()
{
    if (!isEnc)
    {
        _text = encrypt(_text, _dictionaryFileName);
        isEnc = true;
    }
    return _text;
}

std::string SubstitutionText::decrypt()
{
    if (isEnc)
    {
        _text = decrypt(_text, _dictionaryFileName);
        isEnc = false;
    }
    return _text;
}

std::ostream& operator<<(std::ostream& os, const SubstitutionText& st) {
    os << "SubstitutionText " << st.getText();
    return os;
}

