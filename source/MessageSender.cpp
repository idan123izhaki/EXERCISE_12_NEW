#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "MessageSender.hpp"

#define INPUT_FILE_NAME "data.txt" 
#define OUTPUT_FILE_NAME "output.txt"

extern bool emptyAdminFileAndQueue;

int MessageSender::showMenu() const
{
	int option;
	std::cout << "\n1. Sign In\n2. Sign Out\n3.Connected Users\n4.Exit\n";
	while (true)
	{
		std::cout << "\nYour choise: ";
		if ((std::cin >> option).good())
		{
			if (option > 0 && option < 5)
				break;
			else
				std::cout << "Please enter one of the numbers from the menu!" << std::endl;
		}
		else
		{
			std::cout << "There is an error with the input, please try again!" << std::endl;
			//Initialize the cin buffer.
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return option;
}


void MessageSender::signIn()
{
	std::lock_guard<std::mutex> lg(m1);
	std::string name;
	std::cout << "Please enter your name: ";
	std::cin >> name;
	std::set<std::string>::iterator it = this->users.find(name);
	if (it != this->users.end())
		std::cout << "The user is already signed in!" << std::endl;
	else
	{
		this->users.insert(name);
		std::cout << "The user signed in successfuly!" << std::endl;
	}
}


void MessageSender::signOut()
{
	std::lock_guard<std::mutex> lg(m1);
	std::string name;
	std::cout << "Please enter your name: ";
	std::cin >> name;
	std::set<std::string>::iterator it = this->users.find(name);
	if (it == this->users.end())
		std::cout << "There is no user with this name!" << std::endl;
	else
	{
		this->users.erase(name);
		std::cout << "The user signed out successfuly!" << std::endl;
	}
}


void MessageSender::printAllConnectedUsers() const
{
	std::lock_guard<std::mutex> lg(m1);
	if (this->users.empty())
	{
		std::cout << "There are no users logged into the system... The system is empty from users!" << std::endl;
		return;
	}
	int count = 0;
	std::cout << "All the users are connect to the system:";
	for (auto it : this->users)
		std::cout << "\nUser number " << ++count << ": " << it;
	std::cout << std::endl;
}


void MessageSender::readAdminFile()
{
	std::string textLine;
	std::ifstream inputFile(INPUT_FILE_NAME);
	if (inputFile.is_open())
	{
		while (getline(inputFile, textLine)) {
			m2.lock();
			this->msgQueue.push(textLine);
			m2.unlock();
			cv_emptyQueue.notify_one();
			//Wating 60 seconds between reading messages from admin file
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		inputFile.close();
	}
	else
		std::cout << "The file "  INPUT_FILE_NAME << " does not exist! can't open this file..." << std::endl;
	
	//Open the file in write mode in order to delete all the text
	
	std::ofstream outputFile(INPUT_FILE_NAME);
	if (outputFile.is_open())
		outputFile.close();
	else
		std::cout << "Can't open the file " << INPUT_FILE_NAME << " in writing mode..." << std::endl;
}


void MessageSender::writeMessagesToUsersFile()
{
	std::unique_lock<std::mutex> ul(m2);
	std::ofstream output(OUTPUT_FILE_NAME);
	while (true)
	{
		cv_emptySystem.wait(ul, [this] { return !this->users.empty(); });
		cv_emptyQueue.wait_for(ul, std::chrono::seconds(2), [this] { return !this->msgQueue.empty(); });
		if (this->msgQueue.empty()) //The cv_userFile is timeout means the admin file is empty!
			break;
		//Here both mutexes are lock, because reading users (from set) + reading messages (from Q).
		m1.lock();
		for (auto it : this->users)
			output << it << ":\"" << this->msgQueue.front() << "\"" << std::endl;
		m1.unlock();
		this->msgQueue.pop();
	}
	//Notify to user there are mo more messages to send
	emptyAdminFileAndQueue = true;
}
