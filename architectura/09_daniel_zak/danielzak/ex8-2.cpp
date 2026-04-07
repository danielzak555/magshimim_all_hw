#include <windows.h>
#include <iostream>

int main()
{
    HANDLE hIn;
	CHAR buff[1024] = {"\0"};
	DWORD read;
	LPCWSTR name = L"testing.txt"; // have to be a wide str anithing else did me error

    hIn = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); // just read the file casually by the msdn

	if (hIn == INVALID_HANDLE_VALUE) // check for error
    {
        std::cout << "error creating" << std::endl;
    }

    if (!ReadFile(hIn, buff, sizeof(buff) - 1, &read, NULL)) // also check for error
    {
        std::cout << "error in reading" << std::endl;
    }

	buff[read] = '\0'; // Null-terminate the string
    std::cout << "Read " << read << " bytes: " << buff << std::endl; // print results

    CloseHandle(hIn);
    return 0;
} // AMIT i hope you like the documentation i did for you :D