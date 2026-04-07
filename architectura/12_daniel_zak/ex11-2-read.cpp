#include <windows.h>
#include <stdio.h>
#include <iostream>
#define FILENAME "gibrish.bin"
#define MAP_NAME "myMap"


int main()
{
    HANDLE h_file = CreateFileA(
        FILENAME,
        GENERIC_WRITE | GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (h_file == INVALID_HANDLE_VALUE)
    {
        printf("Could not open file, error %d\n", GetLastError());
        return 1;
    }

    HANDLE h_map = CreateFileMappingA(
        h_file,
        NULL,
        PAGE_READWRITE,
        0,
        0,
        MAP_NAME);

    if (h_map == NULL)
    {
        printf("Could not create file mapping, error %d\n", GetLastError());
        CloseHandle(h_file);
        return 1;
    }

    std::cout << "File mapping created successfully." << std::endl;
    CloseHandle(h_file);
    CloseHandle(h_map);

    return 0;
}