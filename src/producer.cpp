#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <shared_mutex>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

// Producer writes to area in ram, consumer reads address and prints it out.
//  Will do with shm_open, ftruncuate, nmap.

int main() {
  // Sets memory in ram, and name of area of ram.
  const char* shm_name = "/myregion";
  const size_t shm_size = 100;
  // File directory opens the name of RAM spot. Either creates it, or if it
  // exists, it reads it.
  int fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    std::cout << "didn't work" << std::endl;
    return 0;
  }

  // Resizes the file directory to the shm_size.
  if (ftruncate(fd, shm_size) == -1) {
    std::cout << "didnt work either at truncate" << std::endl;
    close(fd);
    shm_unlink(shm_name);
    return 0;
  }

  // Cast a character pointer to mmap.
  char* ptr = static_cast<char*>(
      mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

  if (ptr == MAP_FAILED) {
    std::cout << "mmap failed" << std::endl;
    close(fd);
    shm_unlink(shm_name);
    return 0;
  }

  const char* message = "Hello shared memory!";
  strncpy(ptr, message, shm_size);
  std::cout << "Message written to shared memory: " << ptr << std::endl;

  
  munmap(ptr, shm_size);
  close(fd);
  // basically make a loop that runs forever, then I can read from RAM while
  // this happens. Read from ram with following command: cat /dev/shm/myregion
  // With myregion being whaetever shm_name is
  /*while (true) {
          sleep(1000);
          } */
  // ^ Keep above loop running forever basically to read in memory. Rerun
  // afterwards without it if closed to end it.

  if (shm_unlink(shm_name) == -1) {
    std::cout << "unlinked" << std::endl;
    return 0;
  }

  return 0;
}
