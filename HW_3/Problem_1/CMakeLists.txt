cmake_minimum_required(VERSION 3.5)
project(Ex4 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE binarySearch.cpp)

add_executable(binarySearch ${SOURCE})