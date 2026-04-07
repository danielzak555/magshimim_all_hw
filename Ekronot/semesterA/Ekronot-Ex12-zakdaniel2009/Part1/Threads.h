#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


void I_Love_Threads();
void call_I_Love_Threads();

void printVector(const std::vector<int>& primes);

void getPrimes(const int begin, const int end, std::vector<int>& primes);
std::vector<int> callGetPrimes(const int begin, const int end);


void writePrimesToFile(const int begin,const int end, std::ofstream& file);
void callWritePrimesMultipleThreads(const int begin, const int end, const std::string& filePath, const int N);
