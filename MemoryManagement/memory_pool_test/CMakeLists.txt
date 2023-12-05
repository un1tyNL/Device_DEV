
add_executable(memory_pool_test
    memory_pool_test.cpp
)
target_link_libraries(memory_pool_test PRIVATE MemoryManagement gtest_main)
target_include_directories(memory_pool_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(memory_pool_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../CoreComponents)