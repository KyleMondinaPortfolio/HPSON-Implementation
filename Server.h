#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <string>
#include <mutex>
#include "Node.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"


class Server: public Node{
	public:
		Server(int g, int p, int sq, int bs);
		void start();
		void start_node(NodeList *nodes);
		void start_server_online(bool *server_online);
		void start_friends(NodeList *friends,std::mutex *mtx, MessageIDBuffer *mbuffer);
		static void handle_client_node(int connfd, int server_buffer_size, NodeList *nodes);
		static void handle_client(int connfd, int server_buffer_size);
		static void handle_client_friends(int connfd, int server_buffer_size, NodeList *friends, std::mutex *mtx, MessageIDBuffer *mbuffer);
	private:
		int server_queue;
		int server_buffer_size;
		
};

#endif
