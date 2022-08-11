cmake_minimum_required(VERSION 3.8)
project(exe_path-tests)

add_subdirectory(.. tests)

add_executable(my_tests tests.cpp)
target_link_libraries(my_tests PRIVATE exe_path::exe_path)