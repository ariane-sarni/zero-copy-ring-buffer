cmake_minimum_required(VERSION 3.10)
project(zero-copy-ring-buffer VERSION 1.0 LANGUAGES CXX)

# Use C++17 (common for high-performance projects like ring buffers)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Executable 1: Producer ---
add_executable(producer src/producer.cpp)

# --- Executable 2: Consumer ---
add_executable(consumer src/consumer.cpp)

# Optional: If you use pthreads (common in ring buffers), add this:
# find_package(Threads REQUIRED)
# target_link_libraries(producer PRIVATE Threads::Threads)
# target_link_libraries(consumer PRIVATE Threads::Threads)