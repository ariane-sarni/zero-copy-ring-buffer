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
// So need to use atomics instead of mutexes, and use a set buffer array size. Probably 1024. 
// First, research atomics.