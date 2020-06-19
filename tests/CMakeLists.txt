add_executable(simple_clock.out simple_clock.cpp)
target_compile_features(simple_clock.out PRIVATE cxx_std_17)
target_compile_options(simple_clock.out
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith>)
target_include_directories(simple_clock.out PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(simple_clock.out Threads::Threads)
add_test(simple_clock simple_clock.out)

add_executable(advanced_clock.out advanced_clock.cpp)
target_compile_features(advanced_clock.out PRIVATE cxx_std_17)
target_compile_options(advanced_clock.out
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith>)
target_include_directories(advanced_clock.out PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(advanced_clock.out Threads::Threads)
add_test(advanced_clock advanced_clock.out)
