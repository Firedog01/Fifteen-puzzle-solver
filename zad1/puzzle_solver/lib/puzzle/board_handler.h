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

    // use this only if table_len == 16
    static bool same16(uint8_t * solved, uint8_t * state);
    static bool sameMod8(uint8_t * solved, uint8_t * state);
    // use this only if table_len % 4 == 0
    static bool sameMod4(uint8_t * solved, uint8_t * state);
    static bool sameAny(uint8_t * solved, uint8_t * state);
};


#endif //ZAD1_BOARD_HANDLER_H
