cmake_minimum_required(VERSION 2.8)
project(brandes_algorithm)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(./include)

set(SOURCE_FILES ./src/main.cc)

add_executable(brandes ${SOURCE_FILES})

enable_testing()
