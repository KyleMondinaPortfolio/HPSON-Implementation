#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "UDPNode.h"
#include "Node.h"

UDPNode::UDPNode(int g, const char *addr, int p):
	guid(g), 
	port(p),
	addr_string(addr)

{
	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0){
		std::cout << "UDPNode " << guid << " error" << std::endl;
		perror("Problem Occured In Trying to Open Socket: ");
		exit(1);
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (inet_pton(AF_INET, addr, &address.sin_addr)<=0){
		std::cout << "UDPNode " << guid << " error" << std::endl;
		perror("Problem Occured In Putting Supplied Address to Address Struct: ");
		exit(1);
	}	
	std::cout<< "UDPNode " << guid << " UDP Socket Address Successfully Assigned" << std::endl;

	
}

