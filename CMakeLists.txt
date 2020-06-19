cmake_minimum_required(VERSION 3.9)

project(timer VERSION 1.1 DESCRIPTION "A simple C++ header-only library to use cross-platform timer functionnalities using only the standard library.")

#example
find_package(Threads REQUIRED)

add_executable(timer_example ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_compile_features(timer_example PRIVATE cxx_std_17)
target_compile_options(timer_example
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith>)

target_include_directories(timer_example PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(timer_example Threads::Threads)

# This is a header only library
add_library(TimerLib INTERFACE)
target_sources(TimerLib INTERFACE ${PROJECT_SOURCE_DIR}/src/Timer.hpp)
target_include_directories(TimerLib INTERFACE ${PROJECT_SOURCE_DIR}/src)

# Tests
enable_testing()
add_subdirectory(tests)
include(CTest)
