#include "../../lib/info/info_bundle.h"

info_bundle::info_bundle() : timer(), length(0), statesProcessed(0), statesVisited(0), maxDepth(1) {
    solution = new ops::operators[ALLOC_BLOCK];
    solTableLen = ALLOC_BLOCK;
    cursor = solution;
}

int info_bundle::getLength() {
    return length;
}

int info_bundle::getStatesVisited() {
    return statesVisited;
}

int info_bundle::getStatesProcessed() {
    return statesProcessed;
}

int info_bundle::getMaxDepth() {
    return maxDepth;
}

double info_bundle::getExecutionTime() {
    double ret = timer.elapsed();
    timer.reset();
    return ret;
}

ops::operators *info_bundle::getSolution() {
    return solution;
}

void info_bundle::addMove(ops::operators op) {
    if(length >= solTableLen) {
        int inum = 0;
        auto newTable = new ops::operators[solTableLen + ALLOC_BLOCK];
        auto jptr = newTable;
        for(auto iptr = solution; inum < solTableLen; iptr++, jptr++, inum++) {
            *jptr = *iptr;
        }
        delete[](solution);
        solution = newTable;
        solTableLen += ALLOC_BLOCK;
    }
    *cursor = op;
    cursor++;
    length++;
}

void info_bundle::incrVisited() {
    statesVisited++;
}

void info_bundle::incrProcessed() {
    statesProcessed++;
}

void info_bundle::setDepth(int depth) {
    if(depth > maxDepth) {
        maxDepth = depth;
    }
}
