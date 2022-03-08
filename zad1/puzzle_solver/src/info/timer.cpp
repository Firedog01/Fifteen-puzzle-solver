#include "../../lib/info/timer.h"

void timer::reset() {
    beg_ = clock_::now();
}

double timer::elapsed() const {
    return std::chrono::duration_cast<millisecond_>
            (clock_::now() - beg_).count();
}
