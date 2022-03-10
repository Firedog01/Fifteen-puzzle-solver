#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>
#include "../includes.h"

struct board {
    uint8_t* table;
    uint8_t table_len;
    uint8_t zeroIdx;
    ops::operators* path;
    uint16_t path_len;

    board(const board* o);
    board(uint8_t* ptr, uint8_t length);
    board(uint8_t* ptr, uint8_t length, uint8_t zeroIdx);
    ~board();
};


#endif //ZAD1_BOARD_H
