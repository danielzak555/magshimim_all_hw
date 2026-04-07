#include "Threads.h"
#include <mutex>

std::mutex mtx;

void I_Love_Threads() {
	std::cout << "I Love Threads" << std::endl;
}
void call_I_Love_Threads() {
	std::thread t1(I_Love_Threads);
	t1.join();
}

void printVector(const std::vector<int>& primes) {
	for (int prime : primes)
	{
		std::cout << prime << " ";
	}
	std::cout << std::endl;
}

void getPrimes(const int begin, const int end, std::vector<int>& primes) {
	for (int num = begin; num <= end; ++num)
	{
		bool isPrime = true;
		for (int i = 2; i * i <= num; ++i)
		{
			if (num % i == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime && num > 1)
		{
			primes.push_back(num);
		}
	}
}
std::vector<int> callGetPrimes(const int begin, const int end) {
	std::vector<int> prime_vec;

	auto start = std::chrono::high_resolution_clock::now();

	std::thread work1(getPrimes, begin, end, std::ref(prime_vec));
	work1.join();

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> elapsed = finish - start;

	std::cout << elapsed.count() << std::endl;

	return prime_vec;

}


void writePrimesToFile(const int begin, const int end, std::ofstream& file) {
	for (int num = begin; num <= end; ++num) {
		if (num <= 1) continue;

		bool isPrime = true;
		for (int i = 2; i * i <= num; ++i) {
			if (num % i == 0) { isPrime = false; break; }
		}
		if (isPrime) {
			mtx.lock();
			file << num << "\n";
			mtx.unlock();
		}
	}
}
void callWritePrimesMultipleThreads(const int begin, const int end, const std::string& filePath, const int N) {
	auto start = std::chrono::high_resolution_clock::now();
	
	std::ofstream outFile(filePath);
	if (!outFile.is_open()) {
		std::cout << "error opening the file" << std::endl;
		return;
	}

	int total_dis = end - begin + 1;
	int chunk = total_dis / N; // like in minecraft :)
	std::vector<std::thread> thread_vec;
	int thr_end = 0;

	for (int i = 0; i < N; ++i) {
		int thr_start = begin + i * chunk;
		if (i == N - 1) {
			thr_end = end;
		}
		else {
			thr_end = thr_start + chunk - 1;
		}
		thread_vec.push_back(std::thread(writePrimesToFile, thr_start, thr_end, std::ref(outFile)));
	}

	for (int i = 0; i < thread_vec.size(); i++) {
		thread_vec[i].join();
	}

	outFile.close();

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> elapsed = finish - start;

	std::cout << elapsed.count() << std::endl;
}