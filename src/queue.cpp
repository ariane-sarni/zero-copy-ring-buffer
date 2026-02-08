// Nothing needs to be initialzied in constructor anymore, all set in header. Set capacity buffer, front back idnex = 0;
#include "queue.h"


bool CircularBuffer::pop(int &val){
	
	
	return true;
};

bool CircularBuffer::push(int val) {
	
	// Grab the current back. Running load to do it. Basically telling the CPU to prioritize this. 
	// So where is it looking currently? 
	int current_back = back.load(std::memory_order_relaxed);
	
	// Where the next index will be. Modulo wrap around of course.
	int next_back = (current_back + 1) % 1024;
	
	// Where is the current front (so reader index)?
	int current_front = front.load(std::memory_order_acquire);
	
	// If it's about to reach the reader, then we are full. Normally we block, in a non-deterministic code space. Here, since we are real time, and deterministic, skip.
	if (next_back == current_front) {
		return false;
	}
	// Set current back index to new value.
	buffer[current_back] = val;
	// Increment index to next.
	back.store(next_back, std::memory_order_release);
	 
	// We are done.
	return true;
}