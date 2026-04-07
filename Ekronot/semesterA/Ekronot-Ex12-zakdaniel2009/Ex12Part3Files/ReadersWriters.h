#pragma once
#include <mutex>
#include <condition_variable>
#include <string>

class ReadersWriters{
private:
	std::mutex _mu;
	std::unique_lock<std::mutex> _locker;
	std::condition_variable _condW;
	std::condition_variable _condR;
	int _readersNumber;
	int _writersNumber;
	std::string _fileName;

public:
	ReadersWriters(std::string fileName);
	void readLock();
	void writeLock();
	void readUnlock();
	void writeUnlock();
	std::string readLine(int lineNumber); //lineNumber - line number to read
	void WriteLine(int lineNumber, std::string newLine);//lineNumber - line number to write 
};


