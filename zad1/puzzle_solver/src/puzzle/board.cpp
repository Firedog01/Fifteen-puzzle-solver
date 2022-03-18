#include "../../lib/puzzle/board.h"

uint8_t board::len;
uint8_t board::width;
uint8_t board::height;

board::board(uint8_t *ptr) : table(ptr), lastOp(ops::Undefined) {
    int i = 0;
    uint8_t* cursor = table;
    while(i < len && !!*cursor) {
        i++;
        cursor++;
    }
    zeroIdx = i;
}

board::board(const board *o) : zeroIdx(o->zeroIdx), lastOp(ops::Undefined) {
    table = new uint8_t[len];
    std::copy(o->table, o->table + len, table);
}

board::board(const board* o, ops::operators newOp) : zeroIdx(o->zeroIdx), lastOp(newOp) {
    table = new uint8_t[len];
    std::copy(o->table, o->table + len, table);
}

board::board(uint8_t *ptr, uint8_t zeroIdx) :
    table(ptr), zeroIdx(zeroIdx), lastOp(ops::Undefined) {}


board::~board() {
    delete[](table);
}

void board::init_same() {
    if(board::len % 8 == 0) {
        same = &board::sameMod8;
    } else if(board::len % 4 == 0) {
        same = &board::sameMod4;
    } else {
        same = &board::sameAny;
    }
}

bool board::sameMod8(uint8_t* solved, uint8_t* state) {
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

bool board::sameMod4(uint8_t* solved, uint8_t* state) {
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

bool board::sameAny(uint8_t* solved, uint8_t* state) {
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


bool board::operator==(const board &other) const {
    return same(this->table, other.table);
}
