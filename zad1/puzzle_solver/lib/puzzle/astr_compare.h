#ifndef ZAD1_ASTR_COMPARE_H
#define ZAD1_ASTR_COMPARE_H

#include "state_astr.h"

struct astr_compare {
	bool operator()(const state_astr& lhs, const state_astr& rhs) {
		return lhs.f > rhs.f;
	}
};

#endif //ZAD1_ASTR_COMPARE_H
