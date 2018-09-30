cmake_minimum_required(VERSION 3.0)

project(timer)

add_definitions(-std=c++17)
if(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
endif(UNIX)

set(SRCS
src/main.cpp
)

include_directories(timer PRIVATE ./src ./test)
add_executable(timer ${SRCS})
