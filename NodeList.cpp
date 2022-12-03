#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include "NodeList.h"
#include "Client.h"


using namespace std;

NodeList::NodeList(char const *file_name){
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
		Client user(stoi(guid), addr.c_str(), stoi(p));
		if ((add(user))<0){
			cout << "failed to add user: " << guid << " to the Node List" << endl;
		}else{
			cout << "added user: " << guid << " to the Node List"  << endl;
		}
		
	}
	users_file.close();
}
int NodeList::add(Client user){
	nodes.insert({user.name(),user});	
	return 1;
}

void NodeList::send_to_all(Message msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		itr->second.send_msg(msg);
	}
}

void NodeList::send_to_all(std::string msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		itr->second.send_text(msg);
	}
}

void NodeList::send_to(int guid, Message msg){
	Client &client = nodes.at(guid);
	client.send_msg(msg);
}


void NodeList::monitor_failures(bool invisible, int cooldown){
        while(1){
                if (!invisible){
                        cout << "Running Failure Monitors" << endl;
                }
                for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
                        bool is_connected = itr->second.check_connection();
                        if (is_connected){
                                if (!invisible){
                                cout << "Client: " << itr->second.name() << " Connected" << endl;
                                }
                                Message ping("ping",0,0,0,0,"ping~");
                                itr->second.send_msg(ping);
                        }
                        else{
                                if (!invisible){
                                        cout << "Client: " << itr->second.name() << " Not Connected" << endl;
                                }
                                itr->second.try_connect();
                        }
                }
                this_thread::sleep_for(chrono::seconds(cooldown));
        }
}


void NodeList::send_to_all_except(int guid, std::string msg){
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		if (itr->second.name() != guid){
			itr->second.send_text(msg);
		}
	} 
}



void NodeList::show(){
	cout << "Users: " << endl;
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		cout << itr->first << endl;
	} 
	
}

