#ifndef ZAD1_STATE_ASTR_H
#define ZAD1_STATE_ASTR_H

#include "../includes.h"

struct state_astr {
	uint16_t f;
	board b;
	op_path p;

	state_astr(uint16_t f, const board& b, const op_path& p) : f(f), b(b), p(p) {}
	state_astr(const board& b, const op_path& p) : f(0), b(b), p(p) {}
	explicit state_astr(const state& s) : f(0), b(s.first), p(s.second) {}
	state_astr(const state_astr& sa) : f(sa.f), b(sa.b), p(sa.p) {}

	static state get_state(const state_astr& sa) {
		return std::make_pair(sa.b, sa.p);
	}
};


#endif //ZAD1_STATE_ASTR_H
