cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pat_1003.cpp)
add_executable(main ${SOURCE_FILES})