#include "../../lib/puzzle/board.h"

#include <utility>

uint8_t board::len;
uint8_t board::width;
uint8_t board::height;
bool (*board::same)(const uint8_t* first, const uint8_t* second);

board::board(std::vector<uint8_t>  table) : table(std::move(table)) {
    auto it = std::find(this->table.begin(), this->table.end(), 0);
    zero_idx = it - this->table.begin(); // if no zero was found zero_idx = table.length()
}


board::board(const board& o) : zero_idx(o.zero_idx), table(o.table) {}


void board::init_same() {
    if(board::len % 8 == 0) {
        same = &board::same_mod8;
    } else if(board::len % 4 == 0) {
        same = &board::same_mod4;
    } else {
        same = &board::same_any;
    }
}

bool board::same_mod8(const uint8_t* solved, const uint8_t* state) {
    auto solved_ptr = (uint64_t *)solved,
         state_ptr = (uint64_t *)state;
    uint8_t steps = board::len >> 3;
    bool retVal = true;
    for(uint8_t i = 0; i < steps; i++, solved_ptr++, state_ptr++) {
        if((*solved_ptr ^ *state_ptr) != 0) { // 0 if same
            retVal = false;
        }
    }
    return retVal;
}

bool board::same_mod4(const uint8_t* solved, const uint8_t* state) {
    auto solved_ptr = (uint32_t *)solved,
            state_ptr = (uint32_t *)state;
    uint8_t steps = board::len >> 2;
    bool retVal = true;
    for(uint8_t i = 0; i < steps; i++, solved_ptr++, state_ptr++) {
        if(*solved_ptr ^ *state_ptr) {
            retVal = false;
        }
    }
    return retVal;
}

bool board::same_any(const uint8_t* solved, const uint8_t* state) {
    auto solved_ptr = solved,
         state_ptr = state;

    bool retVal = true;
    for(uint8_t i = 0; i < board::len; i++, solved_ptr++, state_ptr++) {
        if(*solved_ptr ^ *state_ptr) {
            retVal = false;
        }
    }
    return retVal;
}


bool board::operator==(const board &other) const {
    if(same == &board::same_mod8 || same == &board::same_mod4 || same == &board::same_any) {
        return same(this->table.data(), other.table.data());
    }
    return false;
}

board& board::operator=(const board &other) {
    zero_idx = other.zero_idx;
    table = other.table;
    return *this;
}
