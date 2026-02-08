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
# 
# # --- Formatting Target ---

# 1. Find the clang-format executable
find_program(CLANG_FORMAT "clang-format")

if(CLANG_FORMAT)
    # 2. Get all source files in the src directory
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        "src/*.cpp" 
        "src/*.h"
    )

    # 3. Add a custom target named 'format'
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting source code with clang-format..."
    )
else()
    message(WARNING "clang-format not found. The 'format' target will not be available.")
endif()