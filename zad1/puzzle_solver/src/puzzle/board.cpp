#include "../../lib/puzzle/board.h"


board::board(uint8_t *ptr, uint8_t length) : begin(ptr), length(length) {
    int i = 0;
    uint8_t* cursor = begin;
    while(i < length && !!*cursor) {
        i++;
        cursor++;
    }
    zeroIdx = i;
}

board::board(uint8_t *ptr, uint8_t length, uint8_t zeroIdx) : begin(ptr), length(length), zeroIdx(zeroIdx) {}
