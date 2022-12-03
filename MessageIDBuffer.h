#ifndef MESSAGEIDBUFFER_H 
#define MESSAGEIDBUFFER_H
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

class MessageIDBuffer{

	public:
		bool add(int message_id);
		bool contains(int message_id);
	private:
		std::vector<int> message_ids;
};



#endif
