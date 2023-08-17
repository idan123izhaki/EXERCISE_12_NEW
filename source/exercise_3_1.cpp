#include <iostream>
#include <thread>
#include <atomic>
#define ARRAY_SIZE 10

void printNumbers(int number);
std::atomic<bool> flag = false; //false = ready to write, true = now writing.

int main()
{
	std::thread threadsArr[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; ++i)
		threadsArr[i] = std::thread(printNumbers, i + 1);

	for (int i = 0; i < ARRAY_SIZE; ++i)
		threadsArr[i].join();
	return 0;
}

void printNumbers(int number)
{
	bool exchange = false;
	for (int i = 0; i < 100; ++i)
	{
		while (!flag.compare_exchange_weak(exchange, true)) exchange = false;	
		std::cout << number << std::endl;
		flag.store(false);
	}
}
