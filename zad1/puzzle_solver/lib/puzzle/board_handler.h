#ifndef ZAD1_BOARD_HANDLER_H
#define ZAD1_BOARD_HANDLER_H

#include <cstdint>
#include "../includes.h"
#include "board.h"


class board_handler {
    board_handler() = default; // static class
public:
    static board* createMoved(board* board, ops::operators op);

    static uint8_t* getSolvedTable(uint16_t length);

    // use this only if table_len == 16
    static bool sameMod16(uint8_t * solved, uint8_t * state, uint8_t length);
    // use this only if table_len % 4 == 0
    static bool sameMod4(uint8_t * solved, uint8_t * state, uint8_t length);
    static bool sameAny(uint8_t * solved, uint8_t * state, uint8_t length);
};


#endif //ZAD1_BOARD_HANDLER_H
