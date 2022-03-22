#include "../../lib/info/info_bundle.h"

info_bundle::info_bundle() : timer(), statesProcessed(0), statesVisited(0), maxDepth(1) {}

double info_bundle::getExecutionTime() {
    double ret = timer.elapsed();
    return ret;
}

void info_bundle::setMaxDepth(int newDepth) {
    if(newDepth > maxDepth)
        maxDepth = newDepth;
}

int info_bundle::getMaxDepth() const {
    return maxDepth;
}

