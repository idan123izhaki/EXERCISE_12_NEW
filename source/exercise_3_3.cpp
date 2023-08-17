#include <iostream>
#include <thread>

#define THREADS_NUMBER 10

bool choosing[THREADS_NUMBER];
int num[THREADS_NUMBER] = {0};

int max(int*);
void printToScreen(int);

int main()
{
	std::thread threadArr[THREADS_NUMBER];
	for (int i = 0; i < THREADS_NUMBER; ++i)
		threadArr[i] = std::thread(printToScreen, i);

	for (int i = 0; i < THREADS_NUMBER; ++i)
		threadArr[i].join();

	return 0;
}

//returns the max number in arr
int max(int* arr)
{
	int maxNumber = arr[0];
	for (int i = 1; i < THREADS_NUMBER; ++i)
	{
		if (arr[i] > maxNumber)
			maxNumber = arr[i];
	}
	return maxNumber;
}


//using bakery algorithem
void printToScreen(int threadNum)
{
	choosing[threadNum] = true;
	num[threadNum] = max(num) + 1;
	choosing[threadNum] = false;

	for (int i = 0; i < THREADS_NUMBER; ++i)
	{
		while (choosing[i]);
		while ((num[i] != 0) && (num[threadNum] > num[i] || (num[threadNum] == num[i] && threadNum > i)));
	}
	std::cout << "Hello! I'm thread number: " << threadNum << std::endl;
	num[threadNum] = 0;
}
