#include <windows.h>
#include <stdio.h>
#include <iostream>
#define FILENAME "gibrish.bin"
#define MAP_NAME "myMap"
#define CHANGE_FIRST_LETTER_TO "Z"

int main(){
    HANDLE h_map = OpenFileMappingA(
        FILE_MAP_WRITE,
        FALSE,
        MAP_NAME);

    if(h_map == NULL){
        printf("Could not open file mapping, error %d\n", GetLastError());
        return 1;
    }

    LPSTR p_buf = (LPSTR)MapViewOfFile(
        h_map,
        FILE_MAP_WRITE,
        0,
        0,
        0);

    if(p_buf == NULL){
        printf("Could not map view of file, error %d\n", GetLastError());
        CloseHandle(h_map);
        return 1;
    }

    p_buf[0] = CHANGE_FIRST_LETTER_TO[0];

    std::cout << "First letter changed successfully." << std::endl;

    UnmapViewOfFile(p_buf);
    CloseHandle(h_map);
    return 0;
    
}