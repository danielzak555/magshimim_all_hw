#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

#define NUM_OF_PHILOSOPHERS 5
#define TIMES_TO_EAT 1000000

const std::string PHILOSOPHER_EXE = "ex10-philosopher.exe";

int main() {
    HANDLE philosophers[NUM_OF_PHILOSOPHERS];
    HANDLE mutexes[NUM_OF_PHILOSOPHERS];

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; ++i) {
        mutexes[i] = CreateMutexA(NULL, FALSE, ("Fork_" + std::to_string(i)).c_str());  // here we create the mutexes for each fork
        if (mutexes[i] == NULL) {
            std::cout << "Failed to create mutex for Fork " << i << std::endl;
            return 1;
        }
    }

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; ++i) { // creating the actual processes
        std::string command = PHILOSOPHER_EXE + " " + std::to_string(i);
        PROCESS_INFORMATION pi;
        STARTUPINFOA si = { sizeof(STARTUPINFOA) };

        if(CreateProcessA(NULL, command.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            philosophers[i] = pi.hProcess;
            CloseHandle(pi.hThread);
        } else {
            std::cout << "Failed to create process for Philosopher " << i << std::endl; // to make sure every thing is ok
            return 1;
        }

    }

    WaitForMultipleObjects(NUM_OF_PHILOSOPHERS, philosophers, true, INFINITE); // be polite and wait for everyone to finish comsuming their food :)

    std::cout << "All philosophers have finished eating." << std::endl;

    for(int i = 0; i < NUM_OF_PHILOSOPHERS; ++i){ // samll cleanup
        CloseHandle(mutexes[i]);
        CloseHandle(philosophers[i]);
    }

    return 0;
}