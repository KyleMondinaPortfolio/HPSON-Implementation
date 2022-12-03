#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>


class Message{
	public:
		Message(std::string t, int sg, int tg, int ts, int mid, std::string m):
			type(t), sguid(sg), tguid(tg), timestamp(ts), message_id(mid), msg(m) {}
		std::string mtype() const {return type;}
		int msguid() const {return sguid;}
		int mtguid() const {return tguid;}
		int mtimestamp() const {return timestamp;}
		int mid() const {return message_id;}
		std::string mmsg() const {return msg;}
	private:
		std::string type;
		int sguid;
		int tguid;
		int timestamp;
		int message_id;
		std::string msg;
		
};

std::string format_msg(Message msg);
Message parse_msg(std::string msg_str);

#endif
