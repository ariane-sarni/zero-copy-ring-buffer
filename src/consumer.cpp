#include "queue.h"

int main() {
  const char *shm_name = "/myregion";
  const size_t shm_size = sizeof(CircularBuffer);
  int fd = shm_open(shm_name, O_RDWR, S_IRUSR);
  if (fd == -1) {
    std::cout << "Couldn't open file." << std::endl;
    return 0;
  }

  // Resizes the file directory to the shm_size.
  if (ftruncate(fd, shm_size) == -1) {
    std::cout << "Couldn't truncate information" << std::endl;
    close(fd);
    shm_unlink(shm_name);
    return 0;
  }

  CircularBuffer *ptr = static_cast<CircularBuffer *>(
      mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  // char *ptr =
  // static_cast<char *>(mmap(NULL, shm_size, PROT_READ, MAP_SHARED, fd, 0));

  if (ptr == MAP_FAILED) {
    std::cout << "Mmap failed" << std::endl;
    close(fd);
    shm_unlink(shm_name);
    return 0;
  }

  int val = 0;
  while (true) {
    if (ptr->pop(val)) {
      std::cout << "Popped " << val << std::endl;
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }

  close(fd);
  munmap(ptr, shm_size);

  return 0;
}