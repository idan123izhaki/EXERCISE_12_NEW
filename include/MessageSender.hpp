//#pragma once
//#include <iostream>
//#include <set>
//#include <string>
//#include <queue>
//#include <mutex>
//
//class MessageSender
//{
//public:
//
//	int showMenu() const;
//	void signIn();
//	void signOut();
//	void printAllConnectedUsers() const;
//	void readAdminFile();
//	void writeMessagesToUsersFile();
//
//	std::condition_variable cv_emptyQueue, cv_emptySystem;
//
//private:
//	std::set<std::string> users;
//	std::queue<std::string> msgQueue;
//	mutable std::mutex m1, m2;
//};