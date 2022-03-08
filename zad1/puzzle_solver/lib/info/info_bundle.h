//
// Created by janru on 07.03.2022.
//

#ifndef ZAD1_INFO_BUNDLE_H
#define ZAD1_INFO_BUNDLE_H

#include <chrono>
#include "timer.h"

class info_bundle {
    timer timer;
    unsigned int length;
    unsigned int statesVisited;
    unsigned int statesProcessed;
    unsigned int maxDepth;

public:
    info_bundle();
    unsigned int getLength();
    unsigned int getStatesVisited();
    unsigned int getStatesProcessed();
    unsigned int getMaxDepth();
    double getExecutionTime();
};


#endif //ZAD1_INFO_BUNDLE_H
