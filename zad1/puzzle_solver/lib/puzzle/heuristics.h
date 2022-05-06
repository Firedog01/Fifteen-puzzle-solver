#ifndef ZAD1_HEURISTICS_H
#define ZAD1_HEURISTICS_H

#include <cstdint>
#include "../includes.h"
#include "board.h"
#include "op_path.h"

struct heuristics {
	static uint16_t hamming(state* st, uint8_t* solved);
	static uint16_t manhattan(state* st, uint8_t* solved);
};


#endif //ZAD1_HEURISTICS_H
