cmake_minimum_required(VERSION 3.21)
project(puzzle_solver)

add_executable(puzzle_solver main.cpp src/puzzle/op_path.cpp lib/puzzle/op_path.h)
target_link_libraries(puzzle_solver zad1_lib)