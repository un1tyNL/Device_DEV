
add_executable(queue_test
    queue_test.cpp
)
target_link_libraries(queue_test PRIVATE MemoryManagement gtest_main)
target_include_directories(queue_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(queue_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../CoreComponents)