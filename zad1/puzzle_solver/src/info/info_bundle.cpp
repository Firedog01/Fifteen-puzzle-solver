#include "../../lib/info/info_bundle.h"

info_bundle::info_bundle() : timer(), processed(0), visited(0), max_depth(1) {}

double info_bundle::get_time() {
    double ret = timer.elapsed();
    return ret;
}

void info_bundle::set_max_depth(int new_depth) {
    if(new_depth > max_depth)
        max_depth = new_depth;
}

int info_bundle::get_max_depth() const {
    return max_depth;
}

