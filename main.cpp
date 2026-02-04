// Test code for circular buffer.

#include <iostream>
#include <vector>

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
	
	BufferArray cool(4);
	cool.add(5);
	cool.printBuffer();
	
	
	return 0;
}

