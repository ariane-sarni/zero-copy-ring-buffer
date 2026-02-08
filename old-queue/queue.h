#include <cerrno>
#include <condition_variable>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>
#include <vector>

class CircularBuffer {
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
