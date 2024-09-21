
cmake_minimum_required(VERSION 3.10)
project(Device_t)

# Include GoogleTest
add_subdirectory(Tools/Testing/GoogleTest)

# Include library directories
add_subdirectory(MemoryManagement)
add_subdirectory(MemoryManagement/linked_list_test)
add_subdirectory(MemoryManagement/memory_compression_test)
add_subdirectory(MemoryManagement/memory_pool_test)
add_subdirectory(MemoryManagement/ring_buffer_test)
add_subdirectory(MemoryManagement/queue_test)
add_subdirectory(DeviceManagement)
add_subdirectory(Algorithms/Calculus/Gps)
add_subdirectory(CoreComponents)

# Enable testing
enable_testing()
add_test(NAME linked_list_test COMMAND linked_list_test)
add_test(NAME memory_compression_test COMMAND memory_compression_test)
add_test(NAME memory_pool_test COMMAND memory_pool_test)
add_test(NAME ring_buffer_test COMMAND ring_buffer_test)
add_test(NAME queue_test COMMAND queue_test)
