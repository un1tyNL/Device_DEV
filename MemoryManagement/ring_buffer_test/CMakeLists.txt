
add_executable(ring_buffer_test
    ring_buffer_test.cpp
)
target_link_libraries(ring_buffer_test PRIVATE MemoryManagement gtest_main)
target_include_directories(ring_buffer_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ring_buffer_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../CoreComponents)