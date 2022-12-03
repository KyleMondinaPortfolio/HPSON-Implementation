#ifndef NODELIST_H
#define NODELIST_H
#include "Client.h"
#include "Message.h"
#include <iostream>
#include <iterator>
#include <string>
#include <map>

class NodeList{
	public:
		NodeList() {}
		NodeList(char const *file_name);
		void send_to_all(Message msg); 
		void send_to_all(std::string msg); 
		void send_to_all_except(int guid, std::string msg);
		void send_to(int guid, Message msg);
		void monitor_failures(bool invisible, int cooldown);
	//	void monitor_failures_whileup(bool invisible, int cooldown, bool *server_online);
		//int removeNode(int guid);
		int add(Client usr);
		void show();
	private:
		std::map<int,Client> nodes;	
};

#endif



