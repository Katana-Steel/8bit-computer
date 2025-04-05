cmake_minimum_required(VERSION 3.20)

project(8-bit VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(computer)
add_subdirectory(assembler)
