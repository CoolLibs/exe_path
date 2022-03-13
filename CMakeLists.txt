cmake_minimum_required(VERSION 3.8)

add_library(exe_path)
add_library(exe_path::exe_path ALIAS exe_path)
target_compile_features(exe_path PUBLIC cxx_std_17)

# ---Add source files---
target_include_directories(exe_path PUBLIC include)
target_sources(exe_path PRIVATE src/exe_path.cpp)