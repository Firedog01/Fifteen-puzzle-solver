#ifndef ZAD1_BOARD_HANDLER_H
#define ZAD1_BOARD_HANDLER_H

#include <cstdint>
#include <iostream>
#include <xmmintrin.h>
#include "../includes.h"
#include "board.h"


class board_handler {
    board_handler() = default; // static class
public:
    static board* createMoved(board* old_board, ops::operators op);
    static uint8_t* getSolvedTable();
};


#endif //ZAD1_BOARD_HANDLER_H
