cmake_minimum_required(VERSION 3.26)
project(large_file_sorter)

include_directories(src/)

set(CMAKE_CXX_STANDARD 23)

add_executable(large_file_sorter src/main.cpp)
