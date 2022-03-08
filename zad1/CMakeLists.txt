cmake_minimum_required(VERSION 3.21)
project(zad1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DTARGET_64 ON)          # target 64 bit
set(COMPILE_FLAGS "-m64")   #

add_subdirectory(puzzle_solver)
add_subdirectory(automated_call)

