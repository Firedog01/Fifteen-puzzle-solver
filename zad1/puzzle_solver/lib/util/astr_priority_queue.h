//
// Created by LiptonLeon on 05.05.2022.
//

#ifndef ZAD1_ASTR_PRIORITY_QUEUE_H
#define ZAD1_ASTR_PRIORITY_QUEUE_H


#include <queue>
#include <set>
#include "../puzzle/state_astr.h"
#include "../puzzle/astr_compare.h"

/*
 * std::astr_priority is extended to access container
 */
class astr_priority_queue : public std::priority_queue<state_astr, std::vector<state_astr>, astr_compare> {

public:

    bool has(const state_astr&);
    state_astr get(const state_astr&);

};


#endif //ZAD1_ASTR_PRIORITY_QUEUE_H
