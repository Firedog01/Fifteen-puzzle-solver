#ifndef ZAD1_BOARD_HANDLER_H
#define ZAD1_BOARD_HANDLER_H

#include <cstdint>
#include <iostream>
#include <utility>
#include "../includes.h"
#include "board_hash.h"
#include "op_path.h"


class board_handler {
    board_handler() = default; // static class
public:
    static state* new_moved(const std::pair<board, op_path>& old_state, ops::operators op);
    static uint8_t* new_solved_table();
    static void display_board(const board& b);
};


#endif //ZAD1_BOARD_HANDLER_H
