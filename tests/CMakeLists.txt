cmake_minimum_required(VERSION 3.8)
project(exe_path-tests)

add_subdirectory(.. tests)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE exe_path::exe_path)

# Set warning level
if(MSVC)
    target_compile_options(exe_path PRIVATE /W4)
else()
    target_compile_options(exe_path PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Maybe enable warnings as errors
set(WARNINGS_AS_ERRORS_FOR_EXE_PATH OFF CACHE BOOL "ON iff you want to treat warnings as errors")
if(WARNINGS_AS_ERRORS_FOR_EXE_PATH)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /WX)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
    endif()
endif()