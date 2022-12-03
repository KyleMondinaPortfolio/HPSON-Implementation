#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <sys/socket.h>
#include <string>
#include <mutex>
#include <queue>
#include "Node.h"
#include "UDPNode.h"
#include "UDPNodeList.h"
#include "MessageIDBuffer.h"
#include "TimeStamp.h"

class UDPServer: public UDPNode{
	public:
		UDPServer(int g, int p, int bs);
		void start();
	//	void start_friends(UDPNodeList *friends, std::mutex *mtx,MessageIDBuffer *mbuffer);
		void start_friends(UDPNodeList *friends, std::mutex *mtx,MessageIDBuffer *mbuffer, TimeStamp *ts, std::mutex *tsmtx);
		//void start_friends(NodeList *friends,std::mutex *mtx, MessageIDBuffer *mbuffer);
		//static void handle_client_friends(int connfd, int server_buffer_size, NodeList *friends, std::mutex *mtx, MessageIDBuffer *mbuffer);
		void start_mutual(int *reqts, UDPNodeList *friends, TimeStamp *ts, std::mutex *tsmtx, std::string *state, std::mutex *smtx, int *replies, std::mutex *rmtx, std::queue<int> *mq, std::mutex *mqmtx);
	private:
		int server_buffer_size;
};
#endif
