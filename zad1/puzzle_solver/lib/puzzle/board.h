#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>
#include <algorithm>
#include <iostream>
#include "../includes.h"

// key of hashmap
struct board {
    uint8_t* table;
    uint8_t zeroIdx;
    ops::operators lastOp;

    explicit board(uint8_t* ptr);
    board(uint8_t* ptr, uint8_t zeroIdx);
    explicit board(const board* o); // copy constructor
    board(const board* o, ops::operators newOp); // copy constructor with setting last op
    ~board();

    // for hashing function
    bool operator==(const board &other) const;
    // https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

    static uint8_t len;
    static uint8_t width;
    static uint8_t height;

    static bool (*same)(uint8_t* first, uint8_t* second);
    static bool sameMod8(uint8_t * solved, uint8_t * state);
    static bool sameMod4(uint8_t * solved, uint8_t * state);
    static bool sameAny(uint8_t * solved, uint8_t * state);
    // needs to be called before any comparison
    // but after setting of board::len
    static void init_same();
};


#endif //ZAD1_BOARD_H
