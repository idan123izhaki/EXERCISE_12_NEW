#pragma once
#include <iostream>
#include <mutex>
#include <string>


class philosophers
{
private:
	std::mutex _mu[5];
	std::unique_lock<std::mutex> _fork[5], _screen;
	std::mutex _screenMutex;
	 
public:
	philosophers();
	void writeToScreen(int philIndex, std::string msg);
	void eat(int philIndex);
};
