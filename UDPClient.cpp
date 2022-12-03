#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <string>
#include <iostream>
#include "UDPClient.h"
#include "Message.h"

UDPClient::UDPClient(int g, const char *addr, int p):
	UDPNode(g, addr, p)
{	
}

void UDPClient::send_text(std::string msg) 
{

	std::cout << "Did this Fire?" << std::endl;
	sendto(sockfd,msg.c_str(),msg.size(),MSG_NOSIGNAL,(struct sockaddr*)&address, sizeof(address));
	std::cout << "Did We Send the Message" << std::endl;
	
}
void UDPClient::send_msg(Message msg){
	std::cout << "Did this Fire?" << std::endl;
	std::string msg_str = format_msg(msg);
	sendto(sockfd,msg_str.c_str(),msg_str.size(),MSG_NOSIGNAL,(struct sockaddr*)&address, sizeof(address));
	std::cout << "Did We Send the Message" << std::endl;
}


