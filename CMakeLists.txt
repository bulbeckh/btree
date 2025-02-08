cmake_minimum_required(VERSION 3.22)

project(btree)

## Ensure the avr-g++ compiler is used here - does CMake have assert equiv.s
message(STATUS Using ${CMAKE_C_COMPILER})
message(STATUS Using ${CMAKE_CXX_COMPILER})

## Add BTree library
add_library(btree STATIC 
	src/btmanager.cpp
	src/leafnode.cpp
	src/fallbacknode.cpp
	src/sequencenode.cpp
)

add_executable(example examples/main.cpp)

target_link_libraries(example btree)
target_include_directories(example PUBLIC ./src/)

