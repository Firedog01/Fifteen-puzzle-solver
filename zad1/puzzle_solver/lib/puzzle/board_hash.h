#ifndef ZAD1_BOARD_HASH_H
#define ZAD1_BOARD_HASH_H

#include "board.h"

struct board_hash {
    std::size_t operator()(const board& b) const {
        return 0;
    }
};


#endif //ZAD1_BOARD_HASH_H
