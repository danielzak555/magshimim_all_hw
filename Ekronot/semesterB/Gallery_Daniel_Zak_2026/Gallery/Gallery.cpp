#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include "MemoryAccess.h"
#include "AlbumManager.h"
#include "DatabaseAccess.h"

HANDLE hChildProcess = nullptr;

BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType)
{
    if (dwCtrlType == CTRL_C_EVENT || dwCtrlType == CTRL_BREAK_EVENT) {
        if (hChildProcess != nullptr) {
            TerminateProcess(hChildProcess, 0);
            CloseHandle(hChildProcess);
            hChildProcess = nullptr; 
            return TRUE; 
        }
        return FALSE; 
    }
    return FALSE;
}

int getCommandNumberFromUser()
{
	std::string message("\nPlease enter any command(use number): ");
	std::string numericStr("0123456789");
	
	std::cout << message << std::endl;
	std::string input;
	std::getline(std::cin, input);
	
	while (std::cin.fail() || std::cin.eof() || input.find_first_not_of(numericStr) != std::string::npos) {

		std::cout << "Please enter a number only!" << std::endl;

		if (input.find_first_not_of(numericStr) == std::string::npos) {
			std::cin.clear();
		}

		std::cout << std::endl << message << std::endl;
		std::getline(std::cin, input);
	}
	
	return std::atoi(input.c_str());
}


int main(void)
{
	if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
		std::cerr << "Error: Could not set control handler" << std::endl;
		return 1;
	}

	// initialization data access
	DatabaseAccess dataAccess;

	// initialize album manager
	AlbumManager albumManager(dataAccess);


	std::string albumName;
	std::cout << "Welcome to Gallery!" << std::endl;
	std::cout << "===================" << std::endl;

	time_t now = time(nullptr);// i did it in the middle to get more percise time
	std::stringstream oss;
	oss << std::put_time(localtime(&now), "%d/%m/%Y %H:%M:%S");
	std::string m_creationDate = oss.str();

	std::cout << "Developer: Daniel Zak The King" << std::endl;
	std::cout << "Creation date: " << m_creationDate << std::endl;
	std::cout << "Type " << HELP << " to a list of all supported commands" << std::endl;
	
	do {
		int commandNumber = getCommandNumberFromUser();
		
		try	{
			albumManager.executeCommand(static_cast<CommandType>(commandNumber));
		} catch (std::exception& e) {	
			std::cout << e.what() << std::endl;
		}
	} 
	while (true);
}


