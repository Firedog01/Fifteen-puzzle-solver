cmake_minimum_required(VERSION 3.21)
project(zad1)

set(CMAKE_CXX_STANDARD 17)

add_executable(zad1
        puzzle_solver/main.cpp
        puzzle_solver/src/info/info_bundle.cpp
        puzzle_solver/lib/info/info_bundle.h
        puzzle_solver/src/info/timer.cpp
        puzzle_solver/lib/info/timer.h
        puzzle_solver/lib/includes.h puzzle_solver/src/file/file_handler.cpp puzzle_solver/lib/file/file_handler.h puzzle_solver/src/file/file_info.cpp puzzle_solver/lib/file/file_info.h puzzle_solver/src/file/file_start_state.cpp puzzle_solver/lib/file/file_start_state.h puzzle_solver/src/file/file_end_state.cpp puzzle_solver/lib/file/file_end_state.h puzzle_solver/src/puzzle/board4x4.cpp puzzle_solver/lib/puzzle/board4x4.h puzzle_solver/src/puzzle/boardNxN.cpp puzzle_solver/lib/puzzle/boardNxN.h puzzle_solver/src/manager.cpp puzzle_solver/lib/manager.h puzzle_solver/src/puzzle/boardAdapter.cpp puzzle_solver/lib/puzzle/boardAdapter.h)
