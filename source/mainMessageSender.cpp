#include "MessageSender.hpp"
#include <thread>

MessageSender msgSender;

bool emptyAdminFileAndQueue = false;

int main()
{
	//Creating 2 threads
	std::thread t1(&MessageSender::readAdminFile, &msgSender);
	std::thread t2(&MessageSender::writeMessagesToUsersFile, &msgSender);

	bool whileFlag = true;
	while (whileFlag)
	{
		if (emptyAdminFileAndQueue)
		{
			std::cout << "\n***********************************************************" << std::endl;
			std::cout << "After 61 seconds the Q is stil empty, the admin file is now empty... no more messages!" << std::endl;
			std::cout << "You can exit from the system..." << std::endl;
			std::cout << "***********************************************************" << std::endl;
			emptyAdminFileAndQueue = false;
		}

		int option = msgSender.showMenu();

		switch (option)
		{
		case 1:
			msgSender.signIn();
			msgSender.cv_emptySystem.notify_one();
			break;
		case 2:
			msgSender.signOut();
			break;
		case 3:
			msgSender.printAllConnectedUsers();
			break;
		case 4:
			std::cout << "Exit from the system!\nGood bye!" << std::endl;
			whileFlag = false;
		}
	}

	//If the threads are not done yet- exit anyway.
	std::exit(EXIT_SUCCESS);

	return 0;
}