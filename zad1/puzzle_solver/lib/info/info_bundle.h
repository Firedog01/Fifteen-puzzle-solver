#ifndef ZAD1_INFO_BUNDLE_H
#define ZAD1_INFO_BUNDLE_H

#include <chrono>
#include <string>
#include "timer.h"
#include "../includes.h"

class info_bundle {
    timer timer;
    int maxDepth;
public:
    info_bundle();
    double getExecutionTime();
    int statesVisited;
    int statesProcessed;
    int getMaxDepth() const;
    void setMaxDepth(int newDepth);
};


#endif //ZAD1_INFO_BUNDLE_H
