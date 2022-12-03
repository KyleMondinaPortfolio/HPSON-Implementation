#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include "NodeList.h"
#include "UDPClient.h"
#include "UDPNodeList.h"

using namespace std;

UDPNodeList::UDPNodeList(char const *file_name){
	ifstream users_file(file_name);
	if(users_file){
		cout << "Successfully Open Users File " << endl; 
	}else{
		cout << "Unable to Open Users File" << endl;
	}
	string line;
	while(getline(users_file,line)){
		istringstream file_line(line);
		string guid, addr, p; 
		file_line >> guid;
		file_line >> addr;
		file_line >> p;
		UDPClient user(stoi(guid), addr.c_str(), stoi(p));
		if ((add(user))<0){
			cout << "failed to add user: " << guid << " to the Node List" << endl;
		}else{
			cout << "added user: " << guid << " to the Node List"  << endl;
		}
		
	}
	users_file.close();
}

int UDPNodeList::add(UDPClient user){
	nodes.insert({user.name(),user});	
	return 1;
}

void UDPNodeList::send_to_all(Message msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
			itr->second.send_msg(msg);
	} 
}

void UDPNodeList::send_to_all_except(int guid, std::string msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		if (itr->second.name() != guid){
			itr->second.send_text(msg);
		}
	} 
}
void UDPNodeList::send_to_all_except(int guid, Message msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		if (itr->second.name() != guid){
			itr->second.send_msg(msg);
		}
	} 
}
void UDPNodeList::send_to(int guid, Message msg){
	UDPClient &client = nodes.at(guid);
	client.send_msg(msg);
}

void UDPNodeList::show(){
	cout << "Users: " << endl;
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		cout << itr->first << endl;
	} 
	
}

