#ifndef ZAD1_STATE_ASTR_H
#define ZAD1_STATE_ASTR_H

#include <utility>

#include "../includes.h"
#include "board.h"
#include "op_path.h"

struct state_astr {
	uint16_t f;
	state s;

	state_astr(uint16_t f, state s) : f(f), s(std::move(s)) {}
	state_astr(const board& b, op_path p) : f(0), s(b, p) {}
	explicit state_astr(state s) : f(0), s(std::move(s)) {}
	state_astr(state s, uint16_t f) : f(f), s(std::move(s)) {}
	state_astr(const state_astr& sa) : f(sa.f), s(sa.s) {}
};


#endif //ZAD1_STATE_ASTR_H
