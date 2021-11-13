cmake_minimum_required(VERSION 3.16)
project(testbench)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories(src)

add_executable(testbench src/main.cpp)

add_subdirectory(Tests)