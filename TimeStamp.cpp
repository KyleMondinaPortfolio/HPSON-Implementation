
#include "TimeStamp.h"

void TimeStamp::recieve(int *ts, std::mutex *mtx, int recieved_ts){
	mtx->lock();
	if (recieved_ts>value){
		value = recieved_ts + 1;
	}else{
		value +=1;
	}
	*ts = value;
	mtx->unlock();
	return; 
}

void TimeStamp::send(int *ts, std::mutex *mtx){
	mtx->lock();
	value+=1;
	*ts = value;	
	mtx->unlock();
	return;
}

