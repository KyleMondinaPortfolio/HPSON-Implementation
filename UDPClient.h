#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <sys/socket.h>
#include <string>
#include <chrono>
#include <mutex>
#include "UDPNode.h"
#include "Node.h"
#include "Message.h"

class UDPClient: public UDPNode{
	public: 
		UDPClient(int g, const char *addr, int p);
		void send_text(std::string msg);
		void send_msg(Message msg);
};

#endif
