#include <iostream>
#include <memory.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <shared_mutex>

struct CircularBuffer {
	private:
		std::vector <int> buffer;
		int front = 0;
		int back = 0;
		int capacity;
		int size = 0;
		std::mutex mu;
		std::condition_variable not_full;
		std::condition_variable not_empty;
	
	public:
	
	CircularBuffer(int size) : capacity(size), buffer(size) {}; // Initialization function / constructor when passed the size of the buffer.
	
	
	// Steps in adding:
	// Lock mutex to ensure no other threads are in.
	// Tell other threads we're not full
	// Add
	void add(int val) {
		// Lock the mutex.
		std::unique_lock<std::mutex> lock(mu);
		// Tell this thread: Basically, I am going to sleep until there is space for me to add. So once we are not full.
		not_full.wait(lock, [this]() {return size < capacity;});
		// Set current indx point to new value, then move forward depending on modulo.
		buffer[back] = val;
		back = (back + 1) % capacity;
		
		// Signal to threads that might be waiting for it to not be full that they can move on.
		not_empty.notify_one();
	}
	
	int read() {
		// Lock mutex, should maybe make it shared?
		// No. Should not be shared - reading is not passive here, it removes an item.
		// Create the lock
		std::unique_lock<std::mutex> lock(mu);
		// Check if the size is > 0. If it is, we're good, we can keep going.
		// Otherwise, we wait.
		// This is a lamba expression
		not_empty.wait(lock, [this](){ return size > 0;});
		// Value to return
		int val = buffer[front];
		// Move front, thus allowing 
		front = (front + 1) % capacity;
		size--;
		not_full.notify_one();
		return val;
	}
	
};



int main(){
	
	
	return 0;
}