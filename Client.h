#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <string>
#include <chrono>
#include <mutex>
#include "Node.h"
#include "Message.h"

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p);
		void monitor_failure(bool invisible, int cooldown, std::mutex *mtx, bool *client_online);
		void try_connect();
		void send_text(std::string msg);
		void send_msg(Message msg);
		bool check_connection() const {return connected;}
	private:
		int client_fd;
		bool connected = false;
};

#endif
