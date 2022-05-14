#include "../../lib/puzzle/board_handler.h"


uint8_t *board_handler::new_solved_table() {
    auto solved_table = new uint8_t[board::len];
    auto solved_cursor = solved_table;
    for(uint8_t i = 1; i < board::len; i++, solved_cursor++) {
        *solved_cursor = i;
    }
    *solved_cursor = 0; // last element is 0
    return solved_table;
}

state* board_handler::new_moved(const state& old_state, ops::operators op) {
    uint8_t moved_zero_idx = old_state.first.zero_idx;
	uint8_t op_int = op;
	// enum operators {L, R, U, D, None, NotFound};
	//				   0  1  2  3	  8			9
	//			  +4   4  5  6  7 <--- if path is empty
	if(old_state.second.path.empty())
		op_int += 0b100;
    switch(op_int) {
        case ops::L:
            if(old_state.first.zero_idx % board::width == 0)
                return nullptr;
            if(*(old_state.second.path.end() - 1) == ops::R)
                return nullptr;
            moved_zero_idx--;
            break;
        case ops::R:
            if(old_state.first.zero_idx % board::width == board::width - 1)
                return nullptr;
            if(*(old_state.second.path.end() - 1) == ops::L)
                return nullptr;
            moved_zero_idx++;
            break;
        case ops::U:
            if(old_state.first.zero_idx < board::width)
                return nullptr;
            if(*(old_state.second.path.end() - 1) == ops::D)
                return nullptr;
            moved_zero_idx -= board::width;
            break;
        case ops::D:
            if(old_state.first.zero_idx >= (board::len - board::width))
                return nullptr;
            if(*(old_state.second.path.end() - 1) == ops::U)
                return nullptr;
            moved_zero_idx += board::width;
            break;
		case (ops::L + 4):
			if(old_state.first.zero_idx % board::width == 0)
				return nullptr;
			moved_zero_idx--;
			break;
		case (ops::R + 4):
			if(old_state.first.zero_idx % board::width == board::width - 1)
				return nullptr;
			moved_zero_idx++;
			break;
		case (ops::U + 4):
			if(old_state.first.zero_idx < board::width)
				return nullptr;
			moved_zero_idx -= board::width;
			break;
		case (ops::D + 4):
			if(old_state.first.zero_idx >= (board::len - board::width))
				return nullptr;
			moved_zero_idx += board::width;
			break;
        default:
            break;
    }
    board moved_board(old_state.first); // throws
    op_path moved_path(old_state.second, op);

    uint8_t *ptr_oz = moved_board.table.data(),
            *ptr_nz = moved_board.table.data();
    ptr_oz += old_state.first.zero_idx;
    ptr_nz += moved_zero_idx;
    *ptr_oz = *ptr_nz;
    *ptr_nz = 0;
    moved_board.zero_idx = moved_zero_idx;
    return new state(moved_board, moved_path);
}


void board_handler::display_board(const board& b) {
    for(int i = 0; i < board::len; i++) {
        std::cout << +b.table[i] << " ";
        if(i % 4 == 3)
            std::cout << '\n';
    }
}


