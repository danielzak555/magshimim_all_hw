#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

#define NUM_OF_PHILOSOPHERS 5
#define TIMES_TO_EAT 1000000

CRITICAL_SECTION chopsticks[NUM_OF_PHILOSOPHERS];

struct philosopher_data {
    int id;
};

DWORD WINAPI philosopher(LPVOID param) {
    philosopher_data* data = (philosopher_data*)param;
    int id = data->id;
    int left = id;
    int right = (id + 1) % NUM_OF_PHILOSOPHERS;    // calcing the chopsticks indexes
    int actual_eat = 0;
    clock_t start_time = clock();

    while (actual_eat < TIMES_TO_EAT) {

        if(TryEnterCriticalSection(&chopsticks[left])){

            if(TryEnterCriticalSection(&chopsticks[right])){
                //std::cout << "Philosopher number: " << id << " is eating." << std::endl;  //just for debug
                actual_eat++;
                LeaveCriticalSection(&chopsticks[right]);   
            }
            LeaveCriticalSection(&chopsticks[left]);
        }

    }
    clock_t end_time = clock();

    double total = (double)(end_time - start_time); // calc the clocks

    std::cout << "Philosopher number: " << id << " finished eating the meals in " << (total / CLOCKS_PER_SEC) << " seconds." << std::endl; // casual printing

    return 0;
}

int main() {
    HANDLE philosophers[NUM_OF_PHILOSOPHERS];
    philosopher_data data[NUM_OF_PHILOSOPHERS];
    for (int i = 0; i < NUM_OF_PHILOSOPHERS; ++i) {
        InitializeCriticalSection(&chopsticks[i]);    // herem im initializig the critical section ffor each one
    }
    for (int i = 0; i < NUM_OF_PHILOSOPHERS; ++i) {
        data[i].id = i;
        philosophers[i] = CreateThread(NULL, 0, philosopher, &data[i], 0, NULL);
    }

    WaitForMultipleObjects(NUM_OF_PHILOSOPHERS, philosophers, TRUE, INFINITE);

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; ++i) {
        DeleteCriticalSection(&chopsticks[i]);
        CloseHandle(philosophers[i]);
    }

    return 0;
}