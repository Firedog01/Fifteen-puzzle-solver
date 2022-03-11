#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>
#include "../includes.h"

struct board {
    uint8_t* table;
    uint8_t zeroIdx;
    ops::operators* path;
    uint16_t pathLen;

    board(const board* o, uint16_t tableLen);
    board(uint8_t* ptr, uint16_t length);
    board(uint8_t* ptr, uint8_t zeroIdx, ops::operators* path, uint16_t pathLen);
    ~board();
};


#endif //ZAD1_BOARD_H
