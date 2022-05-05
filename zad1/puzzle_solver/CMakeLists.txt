cmake_minimum_required(VERSION 3.21)
project(puzzle_solver)

add_executable(puzzle_solver main.cpp src/util/astr_priority_queue.cpp lib/util/astr_priority_queue.h lib/util/better_priority_queue.cpp lib/util/better_priority_queue.h lib/util/better_priority_queue.cpp lib/util/better_priority_queue.h)
target_link_libraries(puzzle_solver zad1_lib)