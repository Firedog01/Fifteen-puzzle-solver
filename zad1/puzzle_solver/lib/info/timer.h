#ifndef ZAD1_TIMER_H
#define ZAD1_TIMER_H

// source: https://gist.github.com/gongzhitaao/7062087#file-timer-c-03-cpp-L20

#include <chrono>

class timer {
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    typedef std::chrono::duration<double, std::ratio<1, 1000> > millisecond_;
    std::chrono::time_point<clock_> beg_;

public:
    timer() : beg_(clock_::now()) {}
    void reset();
    double elapsed() const;
};

#endif //ZAD1_TIMER_H
