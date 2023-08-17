#include "philosopher.hpp"


//initialize all the unique_locks to their mutex, without loking it here (using std::defer_lock)
philosophers::philosophers() {}


void philosophers::writeToScreen(int philIndex, std::string msg)
{
	_screen = std::unique_lock<std::mutex>(_screenMutex);
	std::cout << "Philosopher number: " << philIndex <<  ", " << msg << std::endl;
	_screen.unlock();
}

void philosophers::eat(int philIndex)
{
	//philIndex is the left fork number
	int firstFork = philIndex;
	int secondFork = philIndex ? philIndex - 1 : 4;
	std::string first = "left", second = "right";
	if ((philIndex + 1) % 2) {
		std::swap(firstFork, secondFork); std::swap(first, second);
	}
	_fork[firstFork] = std::unique_lock<std::mutex>(_mu[firstFork]);
	writeToScreen(philIndex, "lock the " + first + " fork!");
	_fork[secondFork] = std::unique_lock<std::mutex>(_mu[secondFork]);
	writeToScreen(philIndex, "lock the " + second + " fork!");
	writeToScreen(philIndex, "now eating!");
	_fork[secondFork].unlock();
	_fork[firstFork].unlock();
}
