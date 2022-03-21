#ifndef ZAD1_BOARD_HASH_H
#define ZAD1_BOARD_HASH_H

#include "board.h"

struct board_hash {
    // in my case sizeof(std::size_t) == 8
    std::size_t operator()(const board& b) const {
        auto ptr = b.table.data();
        std::size_t ret = 0;
        for(uint8_t i = 0; i < board::len; i++, ptr++) {
            ret ^= ( (std::size_t)(*ptr) << (8 - (i % 8)) * 8 );
        }
        return ret;
    }
};


#endif //ZAD1_BOARD_HASH_H
