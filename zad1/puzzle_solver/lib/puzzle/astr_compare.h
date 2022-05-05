#ifndef ZAD1_ASTR_COMPARE_H
#define ZAD1_ASTR_COMPARE_H

#include "state_astr.h"

struct astr_compare {
	bool operator()(const state_astr& a, const state_astr& b) {
		return a.f > b.f;
	}
};

#endif //ZAD1_ASTR_COMPARE_H
