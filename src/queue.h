#include <iostream>
#include <memory.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <shared_mutex>


class CircularBuffer{
	private:
		std::vector<int> buffer;
		int front;
		int back;
		int size;
		int capacity;
		std::mutex mu;
		std::condition_variable not_full;
		std::condition_variable not_empty;
		
	public:
	
		CircularBuffer(int size);
		void add(int val);
		int read();
		
};