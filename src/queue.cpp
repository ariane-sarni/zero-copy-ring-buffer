 #include "queue.h"
 
 CircularBuffer::CircularBuffer(int cap) : buffer(cap), front(0), back(0), size(0), capacity(cap) {}
 
 void CircularBuffer::add(int val) {
  // Step 1. Lock this area in memory.
  // Step 2. Check if the buffer has space.
  // If it doesn't, wait. If it does:
  // Step 3. Add the new value
  // Step 4. Move value and wrap it around.
  // Step 5. Signal to read to let it know it is no longer empty, in case of a spin.
  
  // 1. Lock the mutex.
  std::unique_lock<std::mutex> lock(mu);
  
  // Step 2. Check if the buffer has space, spin if it doesn't.
  // PREDICATE IS THE GREEN LIGHT! IF PREDICATE = TRUE, PROCEED. DO NOT SPIN.
  // PROCEED WHILE SIZE < CAPACITY (WHILE THERE IS ROOM.)
  not_full.wait(lock, [this] () {return size < capacity;}); // Predicate goes here. Look at wait definition. Can either take just (lock), or (lock, predicate), 
 // which is a lambda.
 // So this line, first calls wait on that lock. But then it passes it a lambda function (which the following order: Capture, Argument, Body. [], (), {}. 
 // Capturing this object, no arguments, and the body)
 // Basically checks to see if that argument is true. While the predicate is not true, it waits. size < capacity = we are full. so, 5 = 5 = true. 
 // Predicate in function says: (if !p) { spin}. So if not true, spin. if (the size if not greater than the capacity), spin)
 // Is ths size less than the capacity? i.e. is there room? 
 // If there is no room, we spin. 
 // So size < capacity = true if there is room. False if there is no room.
 // so while (!(size < capacity)) { spin }, 0 < 5 = 1, inverted to 0, so we do not spin
 buffer[back] = val;
 back = (back + 1) % capacity;
 size++;
 // Tell the not empty conditional variable to check again.
 not_empty.notify_one();
 }
 
 int CircularBuffer::read() {
  // 1. Lock the mutex. This is not a passive function - cannot allow multiple readers, it changes buffer on read, since it kicks from buffer.
  // 2. Conditional variable check.
  // 3. Grab value to return
  // 4. Move index forward 
  // 5. Signal conditional variable, there is room now (not full)
  // 6. return read value
  std::unique_lock<std::mutex> lock(mu);
 
 not_empty.wait(lock, [this](){return size > 0;});

 int temp = buffer[front];
 front = (front + 1) % capacity;
 size--;
 not_full.notify_one();
 return temp;
 }