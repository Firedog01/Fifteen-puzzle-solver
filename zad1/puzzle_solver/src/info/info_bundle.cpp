#include "../../lib/info/info_bundle.h"

info_bundle::info_bundle() : timer(), statesProcessed(0), statesVisited(0), maxDepth(1) {}

double info_bundle::getExecutionTime() {
    double ret = timer.elapsed();
    timer.reset();
    return ret;
}

