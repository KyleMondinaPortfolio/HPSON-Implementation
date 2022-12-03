
#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <thread>
#include <mutex>

class TimeStamp{
	public:
		void recieve(int *storage,std::mutex *mtx, int recieved_ts);
		void send(int *storage,std::mutex *mtx);
	private:
		int value = 0;
};


#endif

