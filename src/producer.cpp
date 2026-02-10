#include "queue.h"

// Producer writes to area in ram, consumer reads address and prints it out.
//  Will do with shm_open, ftruncuate, nmap.
// Basic steps:
// 1. Set RAM location
// In this instance, our shm_name, under /myregion
// 2. Set a shared memory size.
// In this instance, should be the size of our class, since we already know the
// total size.
// 3. Connect via shm_open, grab fd.
// 4. Truncate file directory to shm size.
// 5. Use mmap to cast a CircularArray object to the physical address.
// 6. Write to object.

// Gonna make it so user manually enters data, just so I can mess with how its done.
// Step 1 - they enter memory name. 
// 

const char* setSharedName(std::string name) {
	
}

int main() {
  // Sets memory in ram, and name of area of ram.
  const char *shm_name = "/myregion";
  const size_t shm_size = sizeof(CircularBuffer);
  // const size_t shm_size = 100;

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
  CircularBuffer *ptr = static_cast<CircularBuffer *>(
      mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  // char *ptr = static_cast<char *>(
  //  mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

  if (ptr == MAP_FAILED) {
    std::cout << "mmap failed" << std::endl;
    close(fd);
    shm_unlink(shm_name);
    return 0;
  }

  // Allocate memory. Basically telling it to initialize, because making it a
  // static pointer earlier is not like constructing it. ALternativley, can call
  // initialization function
  // new (ptr) CircularBuffer();

  // Example with init
  // Easier for me to understand, so doing this instead.
  ptr->init();

  for (int i = 0; i < 10; i++) {
    ptr->push(i);
    std::cout << "Pushing: " << i << std::endl;
    sleep(5);
  }

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
