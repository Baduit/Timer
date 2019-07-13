cmake_minimum_required(VERSION 3.1)

project(timer VERSION 1.1 DESCRIPTION "A simple C++ header-only library to use cross-platform timer functionnalities using only the standard library.")

# Unix specifics flags
if(UNIX)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
    add_definitions(-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g)
endif(UNIX)

add_definitions(-std=c++17)
# add_definitions does not really works for c++ 17 on msvc
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(timer PRIVATE ./src)

#example
add_executable(timer_example src/main.cpp)

# Tests
enable_testing()

add_executable(simple_clock.out tests/simple_clock.cpp)
add_test(simple_clock simple_clock.out)

add_executable(advanced_clock.out tests/advanced_clock.cpp)
add_test(advanced_clock advanced_clock.out)

add_executable(sleeper.out tests/sleeper.cpp)
add_test(sleeper sleeper.out)

add_executable(thread_timer.out tests/thread_timer.cpp)
add_test(thread_timer thread_timer.out)

add_executable(loop_thread_timer.out tests/loop_thread_timer.cpp)
add_test(loop_thread_timer loop_thread_timer.out)

# This is a header only library
add_library(TimerLib INTERFACE)
target_sources(TimerLib INTERFACE Timer.hpp)
target_include_directories(TimerLib INTERFACE ./src)
