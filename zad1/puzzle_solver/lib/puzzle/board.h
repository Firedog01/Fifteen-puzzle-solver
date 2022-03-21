#ifndef ZAD1_BOARD_H
#define ZAD1_BOARD_H

#include <cstdint>
#include <algorithm>
#include <iostream>
#include "../includes.h"

// key of hashmap
struct board {
    std::vector<uint8_t> table;
    uint8_t zeroIdx;

    board(std::vector<uint8_t> table);
    board(const board& o); // copy constructor

    // for hashing function
    bool operator==(const board &other) const;
    // https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

    board& operator=(const board& other);

    static uint8_t len;
    static uint8_t width;
    static uint8_t height;

    static bool (*same)(const uint8_t* first, const uint8_t* second);
    static bool sameMod8(const uint8_t * solved, const uint8_t * state);
    static bool sameMod4(const uint8_t * solved, const uint8_t * state);
    static bool sameAny(const uint8_t * solved, const uint8_t * state);
    // needs to be called before any comparison
    // but after setting of board::len
    static void init_same();
};

#endif //ZAD1_BOARD_H
