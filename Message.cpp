#include <string>
#include "Message.h"

Message parse_msg(std::string msg_str){

	int first = msg_str.find("-");
	int second = msg_str.find("-",first+1);
	int third = msg_str.find("-",second+1);
	int fourth = msg_str.find("-",third+1);
	int fifth = msg_str.find("-",fourth+1);

	std::string type = msg_str.substr(0,first);
	int sguid = std::stoi(msg_str.substr(first+1,second-first-1));
	int tguid = std::stoi(msg_str.substr(second+1,third-second-1));
	int timestamp = std::stoi(msg_str.substr(third+1,fourth-third-1));
	int message_id = std::stoi(msg_str.substr(fourth+1,fifth-fourth-1));
	std::string message = msg_str.substr(fifth+1,msg_str.find("~")-fifth-1);
	return Message(type,sguid,tguid, timestamp, message_id, message);
}

std::string format_msg(Message msg){
		std::string msg_str(msg.mtype() + 
			"-" + std::to_string(msg.msguid()) + 
			"-" + std::to_string(msg.mtguid()) + 
			"-" + std::to_string(msg.mtimestamp()) + 
			"-" + std::to_string(msg.mid()) + 
			"-" + msg.mmsg() + "~");
		return msg_str;
}
