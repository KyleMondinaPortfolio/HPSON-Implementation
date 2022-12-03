#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include "Message.h"
#include "NodeList.h"

class Monitor{
	public:
		Monitor(Client server, Client self);
		void monitor_failure(bool invisible, int cooldown, std::mutex *mtx,bool *client_online);
	private:
		std::map<int,Client> nodes;	
};

Monitor::Monitor(Client server, Client self){
	nodes.insert({1,server});	
	nodes.insert({2,self});	
}

void Monitor::monitor_failure(bool invisible, int cooldown, std::mutex *mtx,bool *client_online){
	while(1){
	   mtx->lock();
		if (!invisible){
			//std::cout << "Running Failure Monitors" << std::endl;
		}

		if (nodes.at(1).check_connection()){
			if (!invisible){ std::cout << nodes.at(1).name() << " Connected" << std::endl; }
			*client_online = true;
			std::cout << "Is Client Online? " << *client_online << std::endl;
			Message ping("ping",0,0,"ping~");
			nodes.at(1).send_msg(ping);
		}else{
			if (!invisible){ std::cout << nodes.at(1).name() << " Not Connected" << std::endl; }
			*client_online = false;
			//tell the other server to exit the accept
			Message ping("ping",0,0,"ping~");
			nodes.at(2).send_msg(ping);
			std::cout << "Is Client Online? " << *client_online << std::endl;
			nodes.at(1).try_connect();
		}
	   mtx->unlock();
		std::this_thread::sleep_for(std::chrono::seconds(cooldown));
	}

}

void server_online_interface(Client *server,bool *server_online){
	while (*server_online == true){
		std::cout << "server_online_interface, is the server oneline" << *server_online << std::endl;
		std::string user_input;
		while((std::getline(std::cin,user_input)) || (*server_online == true)){
		//while(1){
		std::cout << "------while loop running------" << std::endl;
			if (*server_online == false) {break;}		
		//	Message msg = parse_msg(user_input);
		//	server->send_msg(msg);
		}
		std::cout << "broke up out of while loop" << *server_online << std::endl;
	}
}



void driver_code(Client *server, Server *self, bool *server_online){
	while(1){
		std::cout << "What does the driver code think of the server's status" << *server_online << std::endl;
		if (*server_online == true){
			std::cout << "----------Server is Up----------" << std::endl;
			std::thread t1(server_online_interface,server,server_online);
			//std::thread t2(&Server::start_server_online,self,server_online);
			t1.join();
			//t2.join();
		}else{
			std::cout << "----------Server is Down----------" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

//central server code
int main(){

	bool server_online = false;
	bool *server_online_ptr = &server_online;	
	
	Client central_server(1, "54.149.66.46", 8000);
	Client self_client(10, "127.0.0.1", 8000);
	Monitor failure_detector(central_server,self_client);
	//NodeList friends("Friends.txt");
	//friends.show();

	Server self(1,8000,100,1000);

	//client monitoring
	std::mutex mtx;
	std::thread t1(&Monitor::monitor_failure,&failure_detector,false,3,&mtx,server_online_ptr);
	//std::thread t1(&Client::monitor_failure,&central_server,false,1,&mtx,server_online_ptr);
	std::thread t2(driver_code,&central_server,&self,server_online_ptr);
	t1.join();
	t2.join();
	
}

//Message(int sg, int tg, const std::string &t, const std::string &m):
//Client c1(1, "54.149.66.46", 8000);
//Client c3(3, "34.208.184.118", 8000);
/*
int main(){
	Client c1(1, "54.149.66.46", 8000);
	Message msg("post",0,3,"count dankula");
	c1.send_msg(msg);

	Client c1(1, "54.149.66.46", 8000);
	while (1){
		std::string message;
		while(std::getline(std::cin,message)){
			Message msg = parse_msg(message); 
			c1.send_msg(msg);
		}
	}


	//For Server Instance 1
	NodeList nodes("./Users.txt");
	nodes.show();
	Server s(2,8000,100,1000);
	std::thread t1(&Server::node_start,&s,&nodes);
	std::thread t2(&NodeList::monitor_failures,&nodes);
	t1.join();
	t2.join();

	//For Instance 2
	Server s(2,8000,100,1000);
	s.start();

	//For Instance 3
	Server s(3,8000,100,1000);
	s.start();

	return 0;
}
*/


