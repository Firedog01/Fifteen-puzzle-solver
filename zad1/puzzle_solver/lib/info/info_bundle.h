#ifndef ZAD1_INFO_BUNDLE_H
#define ZAD1_INFO_BUNDLE_H

#include <chrono>
#include <string>
#include "timer.h"
#include "../includes.h"

class info_bundle {
    timer timer;

public:
    info_bundle();
    double getExecutionTime();
    int statesVisited;
    int statesProcessed;
    int maxDepth;
};


#endif //ZAD1_INFO_BUNDLE_H
