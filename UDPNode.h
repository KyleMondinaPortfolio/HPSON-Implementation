#ifndef UDPNODE_H
#define UDPNODE_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class UDPNode{
	public:
		UDPNode(int g,const char *addr, int p);
		int name() const {return guid;}
	protected:
		struct sockaddr_in address;
		int sockfd;			
		int guid;
	private:
		int port;
		std::string addr_string;
};

#endif
