cmake_minimum_required(VERSION 3.16)
project(testbench)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories(src)

set(XMACRO_INCLUDE_LIST src/xmacro_stuff/xmacro_definitions.h)
set(UTILS_INCLUDE_LIST src/Utils/constexpr_utils.h)

add_executable(testbench src/main.cpp ${XMACRO_INCLUDE_LIST} ${UTILS_INCLUDE_LIST})

add_subdirectory(Tests)