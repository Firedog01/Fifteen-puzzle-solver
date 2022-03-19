#include "../../lib/puzzle/board_handler.h"


uint8_t *board_handler::getSolvedTable() {
    auto solved_table = new uint8_t[board::len];
    auto solved_cursor = solved_table;
    for(uint8_t i = 1; i < board::len; i++, solved_cursor++) {
        *solved_cursor = i;
    }
    *solved_cursor = 0; // last element is 0
    return solved_table;
}

state *board_handler::new_moved(std::pair<board, op_path> *old_state, ops::operators op) {
    uint8_t movedZeroIdx = old_state->first.zeroIdx;
    switch(op) {
        case ops::L:
            if(old_state->first.zeroIdx % board::width == 0)
                return nullptr;
            if(old_state->second.lastOp == ops::R)
                return nullptr;
            movedZeroIdx--;
            break;
        case ops::R:
            if(old_state->first.zeroIdx % board::width == board::width - 1)
                return nullptr;
            if(old_state->second.lastOp == ops::L)
                return nullptr;
            movedZeroIdx++;
            break;
        case ops::U:
            if(old_state->first.zeroIdx < board::width)
                return nullptr;
            if(old_state->second.lastOp == ops::D)
                return nullptr;
            movedZeroIdx -= board::width;
            break;
        case ops::D:
            if(old_state->first.zeroIdx > (board::len - board::width))
                return nullptr;
            if(old_state->second.lastOp == ops::U)
                return nullptr;
            movedZeroIdx += board::width;
            break;
        case ops::Undefined:
            break;
    }
    board moved_board(old_state->first);
    op_path moved_path(old_state->second, op);
    uint8_t *ptr_oz = moved_board.table,
            *ptr_nz = moved_board.table;
    ptr_oz += old_state->first.zeroIdx;
    ptr_nz += movedZeroIdx;
    *ptr_oz = *ptr_nz;
    *ptr_nz = 0;
    moved_board.zeroIdx = movedZeroIdx;

    return new state(moved_board, moved_path);
}



