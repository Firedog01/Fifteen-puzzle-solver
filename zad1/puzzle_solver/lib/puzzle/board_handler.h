#ifndef ZAD1_BOARD_HANDLER_H
#define ZAD1_BOARD_HANDLER_H

#include <cstdint>
#include "../includes.h"
#include "board.h"


class board_handler {
    board_handler() = default; // static class
public:
    static void move(board* board, ops::operators op);

    // use this only if table_len == 16
    static bool notSameMod16(uint8_t * solved, uint8_t * state, uint8_t length);
    // use this only if table_len % 4 == 0
    static bool notSolvedMod4(uint8_t * solved, uint8_t * state, uint8_t length);
    static bool notSolvedAny(uint8_t * solved, uint8_t * state, uint8_t length);
};


#endif //ZAD1_BOARD_HANDLER_H
