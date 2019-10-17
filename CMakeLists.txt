cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-elide-constructors")

add_executable(untitled main.cpp)

#target_link_libraries (untitled)
#include_directories(.)

