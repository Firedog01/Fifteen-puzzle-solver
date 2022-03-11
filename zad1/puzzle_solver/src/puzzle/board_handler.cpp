#include <iostream>
#include "../../lib/puzzle/board_handler.h"

board* board_handler::createMoved(board* current, ops::operators op) {
    return new board(nullptr, 0);
}


uint8_t *board_handler::getSolvedTable(uint16_t length) {
    auto solved_table = new uint8_t[length];
    auto solved_cursor = solved_table;
    for(uint8_t i = 1; i < length; i++, solved_cursor++) {
        *solved_cursor = i;
    }
    *solved_cursor = 0; // last element is 0
    return solved_table;
}

bool board_handler::sameMod16(uint8_t* solved, uint8_t* state, uint8_t length) {
    auto solvedPtr = (uint64_t *)solved,
         statePtr = (uint64_t *)state;
    uint8_t steps = length >> 3;
    for(uint8_t i = 0; i < steps; i++) {
        if(*solvedPtr ^ *statePtr) { // 0 if same
            return false;
        }
    }
    return true;
}

bool board_handler::sameMod4(uint8_t* solved, uint8_t* state, uint8_t length) {
    auto solvedPtr = (uint32_t *)solved,
         statePtr = (uint32_t *)state;
    uint8_t steps = length >> 2;
    for(uint8_t i = 0; i < steps; i++) {
        if(*solvedPtr ^ *statePtr) {
            return true;
        }
    }
    return false;
}

bool board_handler::sameAny(uint8_t* solved, uint8_t* state, uint8_t length) {
    uint8_t *solvedPtr = solved,
            *statePtr = state;

    for(uint8_t i = 0; i < length; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            return true;
        }
    }
    return false;
}

