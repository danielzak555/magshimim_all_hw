#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include "Threads.h"


int main()
{
	call_I_Love_Threads();

	std::vector<int> primes1;
	getPrimes(58, 100, primes1);

	std::vector<int> primes3 = callGetPrimes(0, 1000);
	primes3 = callGetPrimes(0, 100000);
	primes3 = callGetPrimes(0, 1000000);

	callWritePrimesMultipleThreads(0, 1000, "primes_0_1000.txt", 2);

	callWritePrimesMultipleThreads(0, 100000, "primes_0_100000.txt", 4);

	callWritePrimesMultipleThreads(0, 1000000, "primes_0_1000000.txt", 4);


	system("pause");
	return 0;
}


 
