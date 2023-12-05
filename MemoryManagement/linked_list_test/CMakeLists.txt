
add_executable(linked_list_test
    linked_list_test.cpp
)
target_link_libraries(linked_list_test PRIVATE MemoryManagement gtest_main)
target_include_directories(linked_list_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(linked_list_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../CoreComponents)