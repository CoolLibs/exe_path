cmake_minimum_required(VERSION 3.8)
project(exe_path-tests)

add_subdirectory(.. tests)

add_executable(my_test test.cpp)
target_link_libraries(my_test PRIVATE exe_path::exe_path)