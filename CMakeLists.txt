cmake_minimum_required(VERSION 3.10)
project(Device_t)

# ========================
# 1. Set C++17 Standard
# ========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========================
# 2. Include GoogleTest
# ========================
add_subdirectory(Tools/Testing/GoogleTest)

# ========================
# 3. Include Library Directories
# ========================
add_subdirectory(MemoryManagement)
add_subdirectory(MemoryManagement/linked_list_test)
add_subdirectory(MemoryManagement/linked_list_node_test)
add_subdirectory(MemoryManagement/memory_compression_test)
add_subdirectory(MemoryManagement/ring_buffer_test)
add_subdirectory(MemoryManagement/queue_test)
add_subdirectory(Tools/Testing/test_helper_test)
add_subdirectory(DeviceManagement)
add_subdirectory(Algorithms/Calculus/Gps)
add_subdirectory(CoreComponents)

# ========================
# 4. Enable Testing
# ========================
enable_testing()

# Add Tests
add_test(NAME linked_list_test COMMAND linked_list_test)
add_test(NAME linked_list_node_test COMMAND linked_list_node_test)
add_test(NAME memory_compression_test COMMAND memory_compression_test)
add_test(NAME ring_buffer_test COMMAND ring_buffer_test)
add_test(NAME queue_test COMMAND queue_test)
add_test(NAME test_helper_test COMMAND test_helper_test)
