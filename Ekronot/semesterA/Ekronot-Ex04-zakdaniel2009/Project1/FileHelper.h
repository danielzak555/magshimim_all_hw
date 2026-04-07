#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>

class FileHelper {
public:
    static std::string readFileToString(const std::string& fileName);

    static void writeWordsToFile(const std::string& inputFileName, const std::string& outputFileName);

    static void saveTextInFile(const std::string& text, const std::string& outputFileName);
};

#endif
