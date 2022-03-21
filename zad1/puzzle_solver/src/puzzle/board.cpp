#include "../../lib/puzzle/board.h"

#include <utility>

uint8_t board::len;
uint8_t board::width;
uint8_t board::height;
bool (*board::same)(const uint8_t* first, const uint8_t* second);


board::board(std::vector<uint8_t> table) : table(std::move(table)) {
    auto it = std::find(this->table.begin(), this->table.end(), 0);
    zeroIdx = it - this->table.begin(); // no error handling if no zero was found
}


board::board(const board& o) : zeroIdx(o.zeroIdx), table(o.table) {}


void board::init_same() {
    if(board::len % 8 == 0) {
        same = &board::sameMod8;
    } else if(board::len % 4 == 0) {
        same = &board::sameMod4;
    } else {
        same = &board::sameAny;
    }
}

bool board::sameMod8(const uint8_t* solved, const uint8_t* state) {
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

bool board::sameMod4(const uint8_t* solved, const uint8_t* state) {
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

bool board::sameAny(const uint8_t* solved, const uint8_t* state) {
    auto solvedPtr = solved,
         statePtr = state;

    bool retVal = true;
    for(uint8_t i = 0; i < board::len; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            retVal = false;
        }
    }
    return retVal;
}


bool board::operator==(const board &other) const {
    if(same == &board::sameMod8 || same == &board::sameMod4 || same == &board::sameAny) {
        return same(this->table.data(), other.table.data());
    }
    return false;
}

board& board::operator=(const board &other) {
    zeroIdx = other.zeroIdx;
    table = other.table;
    return *this;
}
