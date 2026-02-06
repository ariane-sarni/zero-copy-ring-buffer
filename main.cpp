// Test code for circular buffer.
// Think of it like a conveyor belt - Producer runs through an empty list, places boxes. Once it hits the end, will not overwrite until empty space.
// Consumer takes an empty space.

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <shared_mutex>
#include <condition_variable>

struct BufferArray{
	private:
		std::vector<int> buffer;
		int capacity;
		int indx = 0;
		int findx = 0;
		int count = 0;
		std::mutex mu;
		std::condition_variable not_empty;
		std::condition_variable not_full;
		
	public:
	BufferArray(int cap) : capacity(cap), buffer(cap) { };

		void add(int x) {
			// could do std::defer_lock to lock it later. Looks like this:
			// std::unique_lock<shared_mutex> lock(mu, std::defer_lock);
			// To clarify, 'lock' is a variable of a unique lock - can be named anything! Wraps around 'mu' shared mutex.
			// If deferred, can lock later as: lock.lock(), and cna be unlocked as: lock.unlock();
			//std::unique_lock<std::shared_mutex> lock(mu);
			// Alternativley, can do with conditional variables and normal mutex. As follows:
			std::unique_lock<std::mutex> lock(mu);
			// If the belt is full, stop spinning. Sleep here.
			not_full.wait(lock, [this]() { return count < capacity;});
			
			buffer[indx] = x;
			findx = (findx + 1) % capacity;
			count++;
			// Must not_empty.notify_one(), since there is now space. 
		}
// Remove would do following:
// Wait if belt is empty. 
// not_empty wait, count > 0
// Tell a waiting producer (adder) that there is now space. 
// Return disappeared value
		
		void printBuffer() {
			std::shared_lock<std::mutex> lock(mu);
			for (int i = 0; i < capacity; i++) {
				std::cout << buffer[i] << std::endl;
			}
		}

};


int main(){
	// Basically a mutex using RAII principles - dies as soon as its out of scope
	//std::mutex mu;	

	// std::shared_lock<std::shared_mutex> lock(mu); 
	// That is a lock for reading! 
	// 
	// std::unique_lock<std::shared_mutex> lock(mu);
	// This is a lock for writing!

// Should use a shared_mutex instead - when I am reaing, do a shared lock. std::shared_lock<std::shared_mutex> lock(rw_lock)
	// Then use that same lock when writing!
	// std::unique_lock<std::shared_mutex> lock(rw_lock);
	// Thats the writer lock. Need a reader lock now.
	// Makes a unique mutex, locks it. This would spin forever.

	BufferArray cool(4);
	
	//std::thread t1(&BufferArray::add, &cool, 1);
	std::thread t1 ([&cool]() {
		cool.add(1);
	});
	t1.join();
	//cool.add(1);
	//cool.add(2);
	//cool.add(3);
	//cool.add(4);
	//cool.add(5);
	//cool.printBuffer();


	return 0;
}
