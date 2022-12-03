#include "MessageIDBuffer.h"
#include <algorithm>

bool MessageIDBuffer::add(int message_id){
	if (contains(message_id)){
		//already in the buffer
		return false;
	}
	else{
		message_ids.push_back(message_id);
		return true;
	}
	
}


bool MessageIDBuffer::contains(int message_id){
	if(std::count(message_ids.begin(), message_ids.end(), message_id)){
		return true;
	}else{
		return false;
	}
}
