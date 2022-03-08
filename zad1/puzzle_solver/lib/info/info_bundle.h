#ifndef ZAD1_INFO_BUNDLE_H
#define ZAD1_INFO_BUNDLE_H

#include <chrono>
#include <string>
#include "timer.h"
#include "../includes.h"

#define ALLOC_BLOCK 100

class info_bundle {
    timer timer;
    ops::operators* solution;
    int solTableLen;
    ops::operators* cursor;
    int length;
    int statesVisited;
    int statesProcessed;
    int maxDepth;

public:
    info_bundle();
    double getExecutionTime();
    ops::operators* getSolution();
    void addMove(ops::operators op);
    int getLength();
    int getStatesVisited();
    void incrVisited();
    int getStatesProcessed();
    void incrProcessed();
    int getMaxDepth();
    void setDepth(int depth);
};


#endif //ZAD1_INFO_BUNDLE_H
