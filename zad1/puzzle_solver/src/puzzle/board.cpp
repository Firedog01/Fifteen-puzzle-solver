#include <iostream>
#include "../../lib/puzzle/board.h"


board::board(uint8_t *ptr, uint8_t length) : begin(ptr), length(length) {
    int i = 0;
    uint8_t* cursor = begin;
    while(i < length && !!*cursor) {
        i++;
        cursor++;
    }
    if (i < length) {
        zeroIdx = i;
    } else throw std::logic_error("no zero in start state file");
}
