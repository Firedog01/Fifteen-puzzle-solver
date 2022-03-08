cmake_minimum_required(VERSION 3.21)
project(zad1)

set(CMAKE_CXX_STANDARD 17)

add_executable(zad1
        puzzle_solver/main.cpp
        puzzle_solver/src/info/info_bundle.cpp
        puzzle_solver/lib/info/info_bundle.h
        puzzle_solver/src/info/timer.cpp
        puzzle_solver/lib/info/timer.h
        puzzle_solver/lib/includes.h)
