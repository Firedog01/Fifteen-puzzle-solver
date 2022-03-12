#include "../../lib/puzzle/board_handler.h"

board* board_handler::createMoved(board* old_board, ops::operators op) {

    uint8_t movedZeroIdx = old_board->zeroIdx;
    switch(op) {
        case ops::L:
            if(old_board->zeroIdx % board::width == 0)
                return nullptr;
            if(old_board->lastOp == ops::R)
                return nullptr;
            movedZeroIdx--;
            break;
        case ops::R:
            if(old_board->zeroIdx % board::width == board::width - 1)
                return nullptr;
            if(old_board->lastOp == ops::L)
                return nullptr;
            movedZeroIdx++;
            break;
        case ops::U:
            if(old_board->zeroIdx < board::width)
                return nullptr;
            if(old_board->lastOp == ops::D)
                return nullptr;
            movedZeroIdx -= board::width;
            break;
        case ops::D:
            if(old_board->zeroIdx > (board::len - board::width))
                return nullptr;
            if(old_board->lastOp == ops::U)
                return nullptr;
            movedZeroIdx += board::width;
            break;
        default: // like that ever gonna happen
            return nullptr;
    }

    // Creating new board after checking legality of move to avoid memory leak
    auto new_board = new board(old_board, op);
    uint8_t *ptr_oz = new_board->table, *ptr_nz = new_board->table;
    ptr_oz += old_board->zeroIdx;
    ptr_nz += movedZeroIdx;
    *ptr_oz = *ptr_nz;
    *ptr_nz = 0;
    new_board->zeroIdx = movedZeroIdx;
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
    bool retVal = true;
    for(uint8_t i = 0; i < steps; i++, solvedPtr++, statePtr++) {
        if((*solvedPtr ^ *statePtr) != 0) { // 0 if same
            retVal = false;
        }
    }
    return retVal;
}

bool board_handler::sameMod4(uint8_t* solved, uint8_t* state) {
    auto solvedPtr = (uint32_t *)solved,
         statePtr = (uint32_t *)state;
    uint8_t steps = board::len >> 2;
    bool retVal = true;
    for(uint8_t i = 0; i < steps; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            retVal = false;
        }
    }
    return retVal;
}

bool board_handler::sameAny(uint8_t* solved, uint8_t* state) {
    uint8_t *solvedPtr = solved,
            *statePtr = state;

    bool retVal = true;
    for(uint8_t i = 0; i < board::len; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            retVal = false;
        }
    }
    return retVal;
}

