#include <iostream>
#include <thread>
#include "philosopher.hpp"
#define THREADS_ARR_SIZE 5

int main()
{
	philosophers ph;

	//creating 5 threads
	std::thread threadsArr[5];
	
	for (int i = 0; i < THREADS_ARR_SIZE; ++i)
		threadsArr[i] = std::thread(&philosophers::eat, &ph, i);
	for (int i = 0; i < THREADS_ARR_SIZE; ++i)
		threadsArr[i].join();

	return 0;
}