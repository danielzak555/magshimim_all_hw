#include "FileHelper.h"
#include <fstream>

std::string FileHelper::readFileToString(const std::string& fileName) {
    std::ifstream in(fileName);
    if (!in)
        return "";

    std::string result;
    char c;

    while (in.get(c)) {
        result += c;
    }

    return result;
}

void FileHelper::writeWordsToFile(const std::string& inputFileName,
    const std::string& outputFileName)
{
    std::ifstream in(inputFileName);
    std::ofstream out(outputFileName);

    if (!in || !out)
        return;

    std::string word;
    char c;

    while (in.get(c))
    {
        if (c == ' ' || c == '\t')
        {
            if (!word.empty()) {
                out << word << "\n";
                word.clear();
            }
        }
        else if (c == '\n')
        {
            if (!word.empty()) {
                out << word << "\n";
                word.clear();
            }
            else {
                out << "\n";
            }
        }
        else
        {
            word += c;
        }
    }

    if (!word.empty()) {
        out << word;
    }
}


void FileHelper::saveTextInFile(const std::string& text, const std::string& outputFileName) {
    std::ofstream out(outputFileName);
    if (!out)
        return;

    out << text;
}
