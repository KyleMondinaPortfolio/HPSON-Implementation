#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include "Message.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"
#include "UDPServer.h"
#include "UDPClient.h"
#include "UDPNodeList.h"
#include "TimeStamp.h"
#include "Interests.h"
	
int guid = 0;
int server_type = 0;

void user_interface(UDPNodeList *friends,Client *server, bool *server_online, TimeStamp *ts, std::mutex *mtx, MessageIDBuffer *mbuffer){

	while(1){
		//blocking parsing user input
	
		std::string message_type;
		std::string user_message;
		int user_id = guid;
		std::string stid;
		int target_id;
		int message_id = rand();

		std::cout << "----User Interface-----" << std::endl; 

		std::cout << "Enter Type of Message You Want" << std::endl; 
		std::getline(std::cin,message_type);

		std::cout << "Enter Target's ID" << std::endl; 
		std::getline(std::cin,stid);
		target_id = std::stoi(stid);

		std::cout << "Enter Message You Want to Broadcast Over the Network" << std::endl; 
		std::getline(std::cin,user_message);

		int time_stamp;
		ts->send(&time_stamp,mtx);
		
		Message formatted_message(message_type,user_id,target_id,time_stamp,message_id,user_message);
		std::cout << "Message that will be sent" <<std::endl;
		std::cout << format_msg(formatted_message) << std::endl;
		std::cout << "Message ID: " << formatted_message.mid() <<std::endl;
		mbuffer->add(message_id);
		std::cout << "Message Time Stamp " << formatted_message.mtimestamp() <<std::endl;

		if (*server_online == true){
			std::cout << "Server is Online" << std::endl;
			std::cout << "Sending User Input to Central Server" << std::endl;
			
			server->send_text(format_msg(formatted_message));
		}else{
			std::cout << "Server is Offline" << std::endl;
			std::cout << "Multicasting User Input to P2P Network" << std::endl;
			//add a time stamp send
			friends->send_to_all_except(guid,formatted_message);
		}
	}
}

void enter_sc( int *reqts, std::mutex *smtx, std::string *state, int *replies, std::mutex *rmtx, TimeStamp *ts, std::mutex *tsmtx, std::queue<int> *mq, std::mutex *qmtx, UDPNodeList *mnodes){
	//Set State to Requesting
	smtx->lock();
	*state = "REQUESTING";
	smtx->unlock();

	//Set Replies to 0
	rmtx->lock();
	*replies = 0;
	rmtx->unlock();

	//set the time stamp
	int time_stamp;
	//set and save the request time stamp, will be used by UDP Server
	ts->send(reqts, tsmtx);
	
	//Set Request to All Peer Nodes
	std::string reqtype("REQUEST");
	
	//message id duplication might send bugs
	Message request_message(reqtype, guid, 0, *reqts, 0, reqtype);
	mnodes->send_to_all(request_message);

	std::cout << "Waiting To Enter CS"<< std::endl;
	while (1){
		std::cout << "Waiting for Replies"<< std::endl;
		rmtx->lock();
		int rpls = *replies;
		std::cout << rpls << std::endl;
		rmtx->unlock();
		if (rpls >= 2){
			std::cout << "Recieved All Replies" << std::endl;
			break;
		}
                std::this_thread::sleep_for(std::chrono::seconds(cooldown));
	}

	std::cout << "Entered CS" << std::endl;
	smtx->lock();
	*state = "EXECUTING";
	smtx->unlock();

	while(1){
		std::string user_input;
		std::getline(std::cin,user_input);
		if (user_input == "EXIT"){break;}
	}
	std::cout << "Exited Now Releasing"<< std::endl;

	//Set Lock To Released
	smtx->lock();
	*state = "RELEASED";
	smtx->unlock();
	ts->send(&time_stamp,tsmtx);

	//SEND Reply to Everyone
	std::string reptype("REPLY");
	qmtx->lock();
	while(!mq->empty()){
		ts->send(&time_stamp, tsmtx);
		int peer = mq->front();
		std::cout << "Sending Reply Message to Peer: " << peer << std::endl;
		mq->pop();
		Message reply_message(reptype, guid, 0, time_stamp, 0, reptype);
		mnodes->send_to(peer,reply_message);
	}
	qmtx->unlock();
}

int main(){

	if (server_type == 0){
		Client c1(1, "54.149.66.46", 8000);
		//UDPClient c1(1, "34.208.184.118", 7000);
		//UDPClient c1(1, "54.202.116.197", 8000);
		//UDPClient c1(1, "54.149.66.46", 7000);
		//UDPClient c1(1, "54.202.92.56", 7000);
		//UDPClient c1(1, "35.92.125.224", 7000);
		Message msg("post",0,0,0,0,"test multicast");
		
		c1.send_msg(msg);
		return 0;
	}
	else if (server_type == 1){
		//Node Client Code
		bool server_online = false;
		Client central_server_heartbeat(1, "54.149.66.46", 9000);
		Client central_server(1, "54.149.66.46", 8000);
		Server self_main(guid,8000,100,1000);
		UDPServer self_friends(guid,7000,1000);

		std::string file_name("./FriendsOf");
		file_name.append(std::to_string(guid));
		file_name.append(".txt");
		std::cout << file_name << std::endl;
		UDPNodeList friends(file_name.c_str());
		//UDPNodeList friends("./FriendsOf3.txt");
		//UDPNodeList friends("./FriendsOf4.txt");
		
		//Failure Detector for Central Server
		std::mutex monitor_mtx;
		std::thread t1(&Client::monitor_failure,&central_server_heartbeat,true,3,&monitor_mtx,&server_online);

		//Main Listener
		std::thread t2(&Server::start, &self_main);
	
		MessageIDBuffer mbuffer;	

		//User Interface
		TimeStamp ts;
		std::mutex tsmtx;
		std::thread t3(user_interface,&friends,&central_server,&server_online,&ts,&tsmtx,&mbuffer);

		//P2P Listener
		std::mutex buffer_mtx; 
		self_friends.start_friends(&friends,&buffer_mtx,&mbuffer,&ts,&tsmtx);

		t1.join();
		t2.join();
		t3.join();
		return 0;

	}else if (server_type == 2){
		//Central Server Code
		NodeList nodes("./Users.txt");
		nodes.show();
		Server self_main(1,8000,100,1000);
		Server self_heart(1,9000,100,1000);

		//for port 8000
		//Main Server
		std::thread t1(&Server::start_node,&self_main,&nodes);
		//Nodes Failure Detector
		std::thread t2(&NodeList::monitor_failures,&nodes,false,3);

		//for port 9000
		//heart beat server: used for client to check the status of the server
		std::thread t3(&Server::start,&self_heart);
		
		t1.join();
		t2.join();
		t3.join();
		return 0;
	}else if (server_type == 3){
	
		//create the peer udp sockets
		std::string file_name("./Mutual");
		file_name.append(std::to_string(guid));
		file_name.append(".txt");
		std::cout << file_name << std::endl;
		UDPNodeList friends(file_name.c_str());
		
		//create the UDP Listening Server
		UDPServer self_friends(guid,6000,1000);

		//Creating the global variables
		int reqts;
		std::string state("RELEASED");
		std::mutex smtx;
		int replies;
		std::mutex rmtx;
		TimeStamp ts;
		std::mutex tsmtx;
		std::queue<int> mq;
		std::mutex qmtx;
		
		std::thread t1(&UDPServer::start_mutual,&self_friends,&reqts, &friends, &ts, &tsmtx, &state, &smtx, &replies, &rmtx, &mq, &qmtx);
		while(1){
			std::string user_input;
			std::getline(std::cin,user_input);
			if (user_input == "ENTER"){
				enter_sc(&reqts,&smtx,&state,&replies,&rmtx,&ts,&tsmtx,&mq,&qmtx,&friends);
			}
			else if (user_input == "EXIT"){break;}
		}
		t1.join();

		
		
	}else{
			
		return 0;
	}
}

	//UDPNodeList friends("./FriendsOf1.txt");
		//std::cout << "Server Type Not Specified" <<std::endl;
		//std::mutex tsmtx;
		//int value;
		//TimeStamp ts;
		//ts.send(&value,&tsmtx);
		//std::cout << "Time Stamp Value shoudl be 1, Actual: " << value << std::endl;	
		//ts.send(&value,&tsmtx);
		//std::cout << "Time Stamp Value shoudl be 2, Actual: " << value << std::endl;	
		//ts.recieve(&value,&tsmtx,5); 
		//std::cout << "Time Stamp Value shoudl be 6, Actual: " << value << std::endl;	
		
		//std::string example("1+cookies,2+cookies|1+cookies,2+cookies|1+cookies,2+cookies");
		//Interests interest(example);
		//interest.show();
		//interest.format();
		//std::string msg("post-1-2-cookies are the best~");
		//Message message = parse_msg(msg);
		//std::cout << message.mmsg() << std::endl; 
		
		//std::string reform = format_msg(message);
		//std::cout << reform << std::endl;


