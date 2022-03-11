#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>
#include <algorithm>
#include <iostream>
#include "../includes.h"

struct board {
    static uint8_t len;
    static uint8_t width;
    static uint8_t height;

    uint8_t* table;
    uint8_t zeroIdx;
    ops::operators* path;
    uint16_t pathLen;

    explicit board(const board* o); // copy constructor
    // copy and add new operator
    // note: this does not move zero in table, just adds to path
    board(const board* o, ops::operators newOp);
    explicit board(uint8_t* ptr);
    board(uint8_t* ptr, uint8_t zeroIdx, ops::operators* path, uint16_t pathLen);
    ~board();
};


#endif //ZAD1_BOARD_H
