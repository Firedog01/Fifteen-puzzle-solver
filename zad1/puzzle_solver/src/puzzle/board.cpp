#include "../../lib/puzzle/board.h"

uint8_t board::len;
uint8_t board::width;
uint8_t board::height;

board::board(uint8_t *ptr) : table(ptr), path(nullptr), pathLen(0) {
    int i = 0;
    uint8_t* cursor = table;
    while(i < len && !!*cursor) {
        i++;
        cursor++;
    }
    zeroIdx = i;
}

board::~board() {
    delete[](table);
    delete[](path);
}

board::board(const board *o) : zeroIdx(o->zeroIdx), pathLen(o->pathLen) {
    table = new uint8_t[len];
    path = new ops::operators[pathLen];
    std::copy(o->table, o->table + len, table);
    std::copy(o->path, o->path + pathLen, path);
}

board::board(const board* o, ops::operators newOp) : zeroIdx(o->zeroIdx), pathLen(o->pathLen + 1) {
    table = new uint8_t[len];
    path = new ops::operators[pathLen];
    std::copy(o->table, o->table + len, table);
    std::copy(o->path, o->path + o->pathLen, path);
    path[pathLen - 1] = newOp;
//    switch(newOp) {
//        case ops::L:
//            if(zeroIdx % board::width == 0) {
//                return nullptr;
//            }
//            zeroIdx--;
//            break;
//        case ops::R:
//            if(zeroIdx % board::width == board::width - 1) {
//                return nullptr;
//            }
//            zeroIdx++;
//            break;
//        case ops::U:
//            if(zeroIdx < board::width) {
//                return nullptr;
//            }
//            zeroIdx -= board::width;
//            break;
//        case ops::D:
//            if(zeroIdx > (board::len - board::width)) {
//                return nullptr;
//            }
//            zeroIdx += board::width;
//
//            break;
//        default: // like that ever gonna happen
//            return nullptr;
//    }
}

board::board(uint8_t *ptr, uint8_t zeroIdx, ops::operators *path, uint16_t pathLen) :
    table(ptr), zeroIdx(zeroIdx), path(path), pathLen(pathLen) {}
