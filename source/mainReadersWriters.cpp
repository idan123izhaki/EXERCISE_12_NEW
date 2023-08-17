#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include "readersWriters.hpp"

#define SIZE_THREADS_ARR 10

int main()
{
	readersWriters rw("example.txt");

	//Writers
	std::thread writingThread1(&readersWriters::writeLine, &rw, 1, "line111");
	std::thread writingThread2(&readersWriters::writeLine, &rw, 2, "***********");
	std::thread writingThread3(&readersWriters::writeLine, &rw, 3, "line333");
	std::thread writingThread4(&readersWriters::writeLine, &rw, 4, "line444");
	std::thread writingThread5(&readersWriters::writeLine, &rw, 10, "$$$$$$$$$$$");
	std::thread writingThread6(&readersWriters::writeLine, &rw, 6, "line555");
	std::thread writingThread7(&readersWriters::writeLine, &rw, 7, "line666");
	std::thread writingThread8(&readersWriters::writeLine, &rw, 8, "NEW_LINE!");

	writingThread1.join();
	writingThread2.join();
	writingThread3.join();
	writingThread4.join();
	writingThread5.join();
	writingThread6.join();
	writingThread7.join();
	writingThread8.join();


	//Readers
	std::thread threadsArr[10];
	srand(time(0));
	for (int i = 0; i < SIZE_THREADS_ARR; ++i)
		threadsArr[i] = std::thread(&readersWriters::readLine, &rw, int(1 + (rand() % 10)));

	for (int i = 0; i < SIZE_THREADS_ARR; ++i)
		threadsArr[i].join();

	return 0;
}
