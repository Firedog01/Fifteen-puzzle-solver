#ifndef ZAD1_INFO_BUNDLE_H
#define ZAD1_INFO_BUNDLE_H

#include <chrono>
#include <string>
#include "timer.h"
#include "../includes.h"

class info_bundle {
    timer _timer;
    int max_depth;
public:
    info_bundle();
    double get_time();
    int visited;
    int processed;
    int get_max_depth() const;
    void set_max_depth(int new_depth);
};


#endif //ZAD1_INFO_BUNDLE_H
