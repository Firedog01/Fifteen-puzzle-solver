#include "../../lib/puzzle/board_handler.h"

board* board_handler::createMoved(board* old_board, ops::operators op) {
    auto new_board = new board(old_board, op);

    switch(op) {
        case ops::L:
            if(old_board->zeroIdx % board::width == 0)
                return nullptr;
            new_board->zeroIdx--;
            break;
        case ops::R:
            if(old_board->zeroIdx % board::width == board::width - 1)
                return nullptr;
            new_board->zeroIdx++;
            break;
        case ops::U:
            if(old_board->zeroIdx < board::width)
                return nullptr;
            new_board->zeroIdx -= board::width;
            break;
        case ops::D:
            if(old_board->zeroIdx > (board::len - board::width))
                return nullptr;
            new_board->zeroIdx += board::width;
            break;
        default: // like that ever gonna happen
            return nullptr;
    }
    uint8_t *ptr_oz = new_board->table, *ptr_nz = new_board->table;
    ptr_oz += old_board->zeroIdx;
    ptr_nz += new_board->zeroIdx;
    *ptr_oz = *ptr_nz;
    *ptr_nz = 0;
    return new_board;
}


uint8_t *board_handler::getSolvedTable() {
    auto solved_table = new uint8_t[board::len];
    auto solved_cursor = solved_table;
    for(uint8_t i = 1; i < board::len; i++, solved_cursor++) {
        *solved_cursor = i;
    }
    *solved_cursor = 0; // last element is 0
    return solved_table;
}

bool board_handler::sameMod16(uint8_t* solved, uint8_t* state) {
    auto solvedPtr = (uint64_t *)solved,
         statePtr = (uint64_t *)state;
    uint8_t steps = board::len >> 3;
    for(uint8_t i = 0; i < steps; i++) {
        if(*solvedPtr ^ *statePtr) { // 0 if same
            return false;
        }
    }
    return true;
}

bool board_handler::sameMod4(uint8_t* solved, uint8_t* state) {
    auto solvedPtr = (uint32_t *)solved,
         statePtr = (uint32_t *)state;
    uint8_t steps = board::len >> 2;
    for(uint8_t i = 0; i < steps; i++) {
        if(*solvedPtr ^ *statePtr) {
            return false;
        }
    }
    return true;
}

bool board_handler::sameAny(uint8_t* solved, uint8_t* state) {
    uint8_t *solvedPtr = solved,
            *statePtr = state;

    for(uint8_t i = 0; i < board::len; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            return false;
        }
    }
    return true;
}

