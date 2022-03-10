#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>

class board {
public:
    uint8_t zeroIdx;
    uint8_t length;
    uint8_t* begin;
    board(uint8_t* ptr, uint8_t length);
    board(uint8_t* ptr, uint8_t length, uint8_t zeroIdx);
};


#endif //ZAD1_BOARD_H
