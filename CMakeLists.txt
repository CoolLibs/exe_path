cmake_minimum_required(VERSION 3.8)

set(WARNINGS_AS_ERRORS_FOR_EXE_PATH OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(exe_path)
add_library(exe_path::exe_path ALIAS exe_path)
target_compile_features(exe_path PUBLIC cxx_std_17)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_EXE_PATH)
    target_include_directories(exe_path PUBLIC include)
else()
    target_include_directories(exe_path SYSTEM PUBLIC include)
endif()
target_sources(exe_path PRIVATE src/exe_path.cpp)

# Set warning level
if(MSVC)
    target_compile_options(exe_path PRIVATE /W4)
else()
    target_compile_options(exe_path PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Maybe enable warnings as errors
if(WARNINGS_AS_ERRORS_FOR_EXE_PATH)
    if(MSVC)
        target_compile_options(exe_path PRIVATE /WX)
    else()
        target_compile_options(exe_path PRIVATE -Werror)
    endif()
endif()