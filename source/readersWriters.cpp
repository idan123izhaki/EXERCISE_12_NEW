#include <iostream>
#include <fstream>
#include <vector>
#include "readersWriters.hpp"


readersWriters::readersWriters(std::string fileName) :
	_readersNumber(0), _writersNumber(0), _fileName(fileName){}


void readersWriters::readLock()
{
	++this->_readersNumber;
	this->_mu.lock();
	std::cout << "number of readers: " << this->_readersNumber << std::endl;
	this->_mu.unlock();
}

void readersWriters::readUnlock()
{
	--this->_readersNumber;
}

void readersWriters::writeLock()
{
	++this->_writersNumber;
	this->_mu.lock();
	std::cout << "number of writers: " << this->_writersNumber << std::endl;
	this->_mu.unlock();
}

void readersWriters::writeUnlock()
{
	--this->_writersNumber;
}


void readersWriters::readLine(int lineNumber) //line number to read
{
	std::shared_lock<std::shared_mutex> lock(_file_mutex); //enable the reading synchronization	
	this->readLock();
	std::ifstream inputFile(this->_fileName);
	if (inputFile.is_open())
	{
		int numberOfLines = 0;
		std::string line;
		while (std::getline(inputFile, line))
		{
			++numberOfLines;
			if (lineNumber == numberOfLines)
			{
				_mu.lock();
				std::cout << "The line number " << lineNumber << " contect is: " << line << std::endl;
				_mu.unlock();
				break;
			}
		}
		if (lineNumber > numberOfLines)
		{
			_mu.lock();
			std::cout << "The requested line doesn't exist." << std::endl;
			_mu.unlock();
		}
	}
	else
	{
		_mu.lock();
		std::cout << "The file can not be open... try again." << std::endl;
		_mu.unlock();
	}
	inputFile.close();
	this->readUnlock();
}

void readersWriters::writeLine(int lineNumber, std::string newLine) //lineNumber - line number to write
{
	std::unique_lock<std::shared_mutex> lock(_file_mutex); //enable the writing synchronization	
	this->writeLock();
	std::fstream inputOutputFile(this->_fileName, std::ios::in | std::ios::out);
	std::vector<std::string> vec;
	std::string line;
	int numberOfLines = 0, tempCursor = 0;
	bool firstTimeOnly = false, usingVector = false;
	if (inputOutputFile.is_open())
	{
		while (getline(inputOutputFile, line))
		{
			++numberOfLines;
			if (usingVector || numberOfLines == lineNumber)
			{
				if (!firstTimeOnly)
					tempCursor = static_cast<int>(inputOutputFile.tellg()) - line.length() - 2;
				
				if (!firstTimeOnly && inputOutputFile.tellg() == -1)
				{
					inputOutputFile.clear();
					inputOutputFile.seekg(0, std::ios::end);
					tempCursor = static_cast<int>(inputOutputFile.tellg()) - line.length();
				}

				if (!firstTimeOnly && line.length() >= newLine.length())
				{
					inputOutputFile.seekp(tempCursor, std::ios::beg);
					inputOutputFile << newLine;
					firstTimeOnly = true;
					break;
				}
				else
				{
					if (!usingVector) vec.push_back(newLine);
					if (line.length() && numberOfLines != lineNumber) // check if the existing line empty AND this is not the first line
						vec.push_back(line);
					firstTimeOnly = true;
					usingVector = true;
				}
			}
		}
		inputOutputFile.clear(); //free the EOF flag
		if (usingVector) //checking if the vector used in this case
		{
			inputOutputFile.seekp(tempCursor, std::ios::beg);
			std::cout << "The cursor in: " << inputOutputFile.tellp() << std::endl;
			int i = 0;
			for (; i<vec.size() -1 ; ++i)
				inputOutputFile << vec[i] << std::endl;
			inputOutputFile << vec[i];
			vec.clear();
			vec.shrink_to_fit();
		}
		else if (lineNumber == numberOfLines + 1 && !usingVector && !firstTimeOnly)
			inputOutputFile << "\n" << newLine;

		else if (lineNumber > numberOfLines || lineNumber <= 0)
			std::cout << "The line you are trying to write to is invalid." << std::endl;
		inputOutputFile.close();
	}
	else
	{
		this->_mu.lock();
		std::cout << "The file can not be open... try again." << std::endl;
		this->_mu.unlock();
	}
	this->writeUnlock();
}
