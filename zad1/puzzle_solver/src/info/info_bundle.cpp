//
// Created by janru on 07.03.2022.
//

#include "../../lib/info/info_bundle.h"

info_bundle::info_bundle() : timer(), length(1), statesProcessed(0), statesVisited(0), maxDepth(1) //?
{}

unsigned int info_bundle::getLength() {
    return length;
}

unsigned int info_bundle::getStatesVisited() {
    return statesVisited;
}

unsigned int info_bundle::getStatesProcessed() {
    return statesProcessed;
}

unsigned int info_bundle::getMaxDepth() {
    return maxDepth;
}

double info_bundle::getExecutionTime() {
    double ret = timer.elapsed();
    timer.reset();
    return ret;
}

const std::string &info_bundle::getExtraInfoFile() {
    return extraInfoFile;
}

void info_bundle::setExtraInfoFile(const std::string &s) {
    extraInfoFile = s;
}
