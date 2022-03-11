#include <algorithm>
#include <iostream>
#include "../../lib/puzzle/board.h"


board::board(uint8_t *ptr, uint16_t length) : table(ptr), path(nullptr), pathLen(0) {
    int i = 0;
    uint8_t* cursor = table;
    while(i < length && !!*cursor) {
        i++;
        cursor++;
    }
    zeroIdx = i;
}

board::~board() {
    delete[](table);
    delete[](path);
}

board::board(const board *o, uint16_t tableLen) : zeroIdx(o->zeroIdx), pathLen(o->pathLen) {
    table = new uint8_t[tableLen];

    if(tableLen % 8 == 0) {
        auto cursor_this = (uint64_t *) table,
             cursor_o = (uint64_t *) o->table;
        uint8_t steps = tableLen >> 3;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else if(tableLen % 4 == 0) {
        auto cursor_this = (uint32_t *) table,
            cursor_o = (uint32_t *) o->table;
        uint8_t steps = tableLen >> 2;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else if(tableLen % 2 == 0) {
        auto cursor_this = (uint16_t *) table,
                cursor_o = (uint16_t *) o->table;
        uint8_t steps = tableLen >> 1;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else {
        std::copy(o->table, o->table + tableLen, table);
    }
    std::copy(o->path, o->path + pathLen, path);
}

board::board(uint8_t *ptr, uint8_t zeroIdx, ops::operators *path, uint16_t pathLen) :
    table(ptr), zeroIdx(zeroIdx), path(path), pathLen(pathLen) {}
