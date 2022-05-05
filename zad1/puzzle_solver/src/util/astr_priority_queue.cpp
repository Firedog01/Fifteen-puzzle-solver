//
// Created by LiptonLeon on 05.05.2022.
//

#include <algorithm>
#include "../../lib/util/astr_priority_queue.h"

bool astr_priority_queue::has(const state_astr& sa) {
    if (std::find(c.begin(), c.end(), sa) != c.end())
        return true;
    return false;
}

state_astr astr_priority_queue::get(const state_astr& sa) {
    return *std::find(c.begin(), c.end(), sa);
}
