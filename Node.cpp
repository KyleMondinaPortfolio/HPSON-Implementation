#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Node.h"

Node::Node(int g, const char *addr, int p):
	guid(g), 
	port(p),
	addr_string(addr)
{
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
		std::cout << "Node " << guid << " error" << std::endl;
		perror("Problem Occured In Trying to Open Socket: ");
		exit(1);
	}
	std::cout<< "Node " << guid << " TCP Socket Successfully Opened" << std::endl;
	
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
		perror("setsockopt: ");
	}
	
	//memset((char *)address, 0, sizeof(*address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	if (inet_pton(AF_INET, addr, &address.sin_addr)<=0){
		std::cout << "Node " << guid << " error" << std::endl;
		perror("Problem Occured In Putting Supplied Address to Address Struct: ");
		exit(1);
	}	
	std::cout<< "Node " << guid << " TCP Socket Address Successfully Assigned" << std::endl;
}

void Node::restart_port()
{
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
		std::cout << "Node " << guid << " error" << std::endl;
		perror("Problem Occured In Trying to Open Socket: ");
		exit(1);
	}
	std::cout<< "Node " << guid << " TCP Socket Successfully Opened" << std::endl;
	
	//memset((char *)address, 0, sizeof(*address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	if (inet_pton(AF_INET, addr_string.c_str(), &address.sin_addr)<=0){
		std::cout << "Node " << guid << " error" << std::endl;
		perror("Problem Occured In Putting Supplied Address to Address Struct: ");
		exit(1);
	}	
	std::cout<< "Node " << guid << " TCP Socket Address Successfully Assigned" << std::endl;

}


