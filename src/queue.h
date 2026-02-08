// Need to do two thigns differnetly from previous queue code:
// 1. Use a set size array. If we allocate on heap, as we did previously with vector, it cannot access the memory. 
// This is because heap memory is program specific. Basically 'producer' writes to its own queue, but consumer cannot read from it, since vector is on heap (I think?)
// 2. Use atomics. 
// Mutex is also only program specific.
// So some lessons:
// VECTOR, even if defined on the stack, ALWAYS allocates new memory on the heap. If the actual vector object lives on the stack, 
// Memory from the vector lives on the heap.
// 
// Mutexes are program specific. Cannot share through seperate programs. 
// 
// So need to use atomics instead of mutexes, and use a set buffer array capacity. Probably 1024. 
// First, research atomics.
// 

// Input/Output
#include <iostream>   // For std::cout, std::cerr

// POSIX Shared Memory & File Handling
#include <fcntl.h>    // For O_CREAT, O_RDWR (File control options)
#include <sys/mman.h> // For mmap, shm_open, munmap, PROT_*, MAP_*
#include <sys/stat.h> // For mode constants (S_IRUSR, S_IWUSR)
#include <unistd.h>   // For ftruncate, close

// Threading & Timing (For the loops)
#include <thread>     // For std::this_thread::sleep_for
#include <chrono>     // For std::chrono::milliseconds
#include <cstdint>    // For uint32_t (Standard fixed-width integers)
#include <atomic>
#include <cstring>

class CircularBuffer{
	// Use atomics, use set buffer capacity.
	// We now no longer need a capacity. It is a set capacity.
	// We also *technically* dont need a 'size' index.
	// front - back = size. 
	private:
		
		int buffer[1024];
		std::atomic <int> front{0};
		std::atomic <int> back{0};
	public:
		bool pop(int &val); // The value that is popped is written to val.
		bool push(int val); // Val is written into buffer.
};