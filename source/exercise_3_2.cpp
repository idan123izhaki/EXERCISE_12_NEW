#include <iostream>
#include <thread>

//Global variables
bool flag[2] = {false, false};
int turn;
int counter = 0; //shared resource
bool whileFlag = true;

void printNumbers(int);

int main()
{
	std::thread t1(printNumbers, 0);
	std::thread t2(printNumbers, 1);
	t1.join();
	t2.join();

	return 0; 
}


void printNumbers(int threadNum)
{
	while (whileFlag)
	{
		flag[threadNum] = true;
		turn = threadNum;
		while (whileFlag && flag[1 - threadNum] && turn == threadNum);
		if (counter < 50)
		{
			std::cout << "Thread number " << threadNum << ", increase the counter. --> " << ++counter << std::endl;
			flag[threadNum] = false;
		}
		else
			whileFlag = false;
	}
}
 