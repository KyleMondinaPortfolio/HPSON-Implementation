#ifndef NODE_H
#define NODE_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class Node{
	public:
		Node(int g,const char *addr, int p);
		int name() const {return guid;}
		void restart_port();
	protected:
		struct sockaddr_in address;
		int sockfd;			
		int guid;
	private:
		int port;
		std::string addr_string;
		int opt = 1;
};

#endif
