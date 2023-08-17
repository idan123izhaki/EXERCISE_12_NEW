#pragma once
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <string>

class readersWriters {
private:
	std::mutex _mu; //mutex for output operations
	std::shared_mutex _file_mutex; //mutex for read/write operationss
	int _readersNumber;
	int _writersNumber;
	std::string _fileName;

public:
	readersWriters(std::string fileName);
	inline void readLock();
	inline void writeLock();
	inline void readUnlock();
	inline void writeUnlock();
	void readLine(int lineNumber); //lineNumber - line number to read
	void writeLine(int lineNumber, std::string newLine);//lineNumber - line number to write 
};
