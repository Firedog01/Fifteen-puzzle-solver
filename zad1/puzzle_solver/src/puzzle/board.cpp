#include <algorithm>
#include <iostream>
#include "../../lib/puzzle/board.h"


board::board(uint8_t *ptr, uint8_t length) : table(ptr), table_len(length), path(nullptr), path_len(0) {
    int i = 0;
    uint8_t* cursor = table;
    while(i < length && !!*cursor) {
        i++;
        cursor++;
    }
    zeroIdx = i;
}

board::board(uint8_t *ptr, uint8_t length, uint8_t zeroIdx) : table(ptr), table_len(length), zeroIdx(zeroIdx) {}

board::~board() {
    delete[](table);
    delete[](path);
}

board::board(const board *o) : table_len(o->table_len), zeroIdx(o->zeroIdx), path_len(o->path_len) {
    table = new uint8_t[table_len];

    if(table_len % 8 == 0) {
        auto cursor_this = (uint64_t *) table,
             cursor_o = (uint64_t *) o->table;
        uint8_t steps = table_len >> 3;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else if(table_len % 4 == 0) {
        auto cursor_this = (uint32_t *) table,
            cursor_o = (uint32_t *) o->table;
        uint8_t steps = table_len >> 2;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else if(table_len % 2 == 0) {
        auto cursor_this = (uint16_t *) table,
                cursor_o = (uint16_t *) o->table;
        uint8_t steps = table_len >> 1;
        for(uint8_t i = 0; i < steps; i++, cursor_o++, cursor_this++) {
            *cursor_this = *cursor_o;
        }
    } else {
        std::copy(o->table, o->table + table_len, table);
    }
    std::copy(o->path, o->path + path_len, path);
}
