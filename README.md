# Zero-Copy Shared Memory Ring Buffer (shm-ring-buffer)

A lock-free, single-producer single-consumer (SPSC) ring buffer implementation using Linux Shared Memory (shm_open) for high-bandwidth Inter-Process Communication (IPC).

### Key Features
* **Zero-Copy Transfer:** Passes data pointers instead of copying memory buffers between processes.
* **Lock-Free Concurrency:** Uses C++20 std::atomic for head/tail synchronization (no Mutexes).
* **Low Latency:** Designed to minimize context switches for real-time robotics data streams.

### Tech Stack
* C++20
* Linux POSIX Shared Memory
* GTest (Unit Testing)

### Build & Run
```bash
mkdir build && cd build
cmake ..
make
./producer & ./consumer
```

### Step 1
- [x] Have two seperate C++ programs (producer, consumer) read/write to memory in RAM.
- [x] Producer writes to area in ram, consumer reads address and prints it out.
(Will do with shm_open, ftruncuate, nmap.)

### Step 2
- [ ] Make a circular array 
- [ ] Showcase circular array on data
- [ ] Make it multithreaded
