cmake_minimum_required(VERSION 3.21)
project(puzzle_solver)

set(SOURCE_FILES
        main.cpp
        src/info/info_bundle.cpp
        src/info/timer.cpp
        src/file/file_handler.cpp
        src/file/file_info.cpp
        src/file/file_start_state.cpp
        src/file/file_end_state.cpp
        src/manager.cpp
        src/puzzle/board.cpp)

add_executable(puzzle_solver ${SOURCE_FILES})