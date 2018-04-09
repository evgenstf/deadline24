cmake_minimum_required(VERSION 2.8.4)
project(deadline24_solutions)

set(CMAKE_CXX_STANDARD 11)

add_executable(solution_a solution_a.cpp)
add_executable(solution_b solution_b.cpp)
add_executable(solution_c solution_c.cpp)
add_executable(deadgram_example deadgram_example.cpp)
target_link_libraries(deadgram_example boost_system pthread)
