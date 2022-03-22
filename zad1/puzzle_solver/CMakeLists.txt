cmake_minimum_required(VERSION 3.21)
project(puzzle_solver)

add_executable(puzzle_solver main.cpp src/strategies.cpp lib/strategies.h)
target_link_libraries(puzzle_solver zad1_lib)