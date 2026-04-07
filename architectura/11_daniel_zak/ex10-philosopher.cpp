#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

#define NUM_OF_PHILOSOPHERS 5
#define TIMES_TO_EAT 1000000

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cout << "wrong nums of arguments" << std::endl;
        return 1;
    }

    int philosopher_id = std::atoi(argv[1]); // some stuupid sh*t from the last year, bearly remembered that
    if (philosopher_id < 0 || philosopher_id >= NUM_OF_PHILOSOPHERS) {
        std::cout << "philosopher id must be between 0 and " << NUM_OF_PHILOSOPHERS - 1 << std::endl;
        return 1;
    }
    int left = philosopher_id;
    int right = (philosopher_id + 1) % NUM_OF_PHILOSOPHERS;

    HANDLE hLeftFork = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, ("Fork_" + std::to_string(left)).c_str()); // open the mutexes by the names
    HANDLE hRightFork = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, ("Fork_" + std::to_string(right)).c_str());

    if (hLeftFork == NULL || hRightFork == NULL) {
        std::cout << "Fail to open the mutexes" << std::endl; // just for safty
        return 1;
    }
    int actual_eat = 0;
    clock_t start_time = clock(); // start timer

    while(actual_eat < TIMES_TO_EAT) {
        if (WaitForSingleObject(hLeftFork, 0) == WAIT_OBJECT_0) {
            if (WaitForSingleObject(hRightFork, 0) == WAIT_OBJECT_0) {
                //std::cout << "Philosopher number: " << philosopher_id << " is eating." << std::endl;  //just for debug
                actual_eat++;
                ReleaseMutex(hRightFork);
            }
            ReleaseMutex(hLeftFork);
        }
    }

    clock_t end_time = clock();
    double total = (double)(end_time - start_time); // calc the clocks
    std::cout << "philosopher number: " << philosopher_id << " finished eating the meals in " << (total / CLOCKS_PER_SEC) << " seconds" << std::endl;

    CloseHandle(hLeftFork);
    CloseHandle(hRightFork);

    return 0;

}