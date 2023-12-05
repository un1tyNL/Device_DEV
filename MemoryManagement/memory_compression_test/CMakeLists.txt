
add_executable(memory_compression_test
    memory_compression_test.cpp
)
target_link_libraries(memory_compression_test PRIVATE MemoryManagement gtest_main)
target_include_directories(memory_compression_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(memory_compression_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../CoreComponents)