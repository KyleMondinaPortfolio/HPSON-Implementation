#ifndef UDPNODELIST_H
#define UDPNODELIST_H
#include "Client.h"
#include "UDPClient.h"
#include "Message.h"
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include "UDPNodeList.h"

class UDPNodeList{
	public:
		UDPNodeList(char const *file_name);
		void send_to_all(Message msg);
		void send_to_all_except(int guid, std::string msg);
		void send_to_all_except(int guid, Message msg);
		void send_to(int guid, Message msg);
		int add(UDPClient usr);
		void show();
	private:
		std::map<int,UDPClient> nodes;	
};

#endif



