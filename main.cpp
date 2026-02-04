// Test code for circular buffer.
// Think of it like a conveyor belt - Producer runs through an empty list, places boxes. Once it hits the end, will not overwrite until empty space.
// Consumer takes an empty space.

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

struct BufferArray{
	private:
		std::vector<int> buffer;
		int capacity;
		int indx = 0;

	public:
	BufferArray(int cap) : capacity(cap), buffer(cap) { };

		void add(int x) {
			indx = indx % capacity;
			buffer[indx] = x;
			indx++;

		}

		void printBuffer() {
			for (int i = 0; i < capacity; i++) {
				std::cout << buffer[i] << std::endl;
			}
		}

};


int main(){
	// Basically a mutex using RAII principles - dies as soon as its out of scope
	std::mutex mu;
	std::unique_lock<std::mutex> lock(mu);
	// Should use a shared_mutex instead - when I am reaing, do a shared lock. std::shared_lock<std::shared_mutex> lock(rw_lock)
	// Then use that same lock when writing!
	// std::unique_lock<std::shared_mutex> lock(rw_lock);
	// Thats the writer lock. Need a reader lock now.
	// Makes a unique mutex, locks it. This would spin forever.

	BufferArray cool(4);
	cool.add(1);
	cool.add(2);
	cool.add(3);
	cool.add(4);
	cool.add(5);
	cool.printBuffer();


	return 0;
}
