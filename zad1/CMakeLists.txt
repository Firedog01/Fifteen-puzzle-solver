cmake_minimum_required(VERSION 3.21)
project(zad1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DTARGET_64 ON)            # target 64 bit
set(COMPILE_FLAGS "-m64 -Ofast")

set(SOURCE_FILES
        puzzle_solver/src/info/info_bundle.cpp
        puzzle_solver/src/info/timer.cpp
        puzzle_solver/src/file_start_state.cpp
        puzzle_solver/src/manager.cpp
        puzzle_solver/src/puzzle/board.cpp
        puzzle_solver/src/puzzle/board_handler.cpp
        puzzle_solver/src/puzzle/op_path.cpp
        puzzle_solver/src/strategies.cpp)

add_library(zad1_lib ${SOURCE_FILES})

add_subdirectory(puzzle_solver)
add_subdirectory(automated_call)

