cmake_minimum_required(VERSION 2.8)
project(brandes_algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -O3 -pthread -march=native")

include_directories(./include)

set(SOURCE_FILES ./src/main.cc
                 ./src/graph.cc
                 ./src/brandes.cc)

add_executable(brandes ${SOURCE_FILES})

