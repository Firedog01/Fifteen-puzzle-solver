#include "../../lib/puzzle/heuristics.h"

// Are numbers in place
uint16_t heuristics::hamming(state* st, const uint8_t *solved) {
	uint16_t ret = 0;
	for(int i = 0; i < board::len; i++) {
		if (st->first.table[i] == 0) // Ignore 0
			continue;
		ret += (st->first.table[i] == solved[i]);
	}
	return ret;
}

/*
 * idx 0 1 2 3 4 5 .. 14 15
 * val 1 2 3 4 5 6 .. 15  0
 */
// Sum distances from number to expected place
uint16_t heuristics::manhattan(state *st, const uint8_t *solved) {
	uint16_t ret = 0;
	for(int i = 0; i < board::height; i++) {
		for(int j = 0; j < board::width; j++) {
			if (st->first.table[i * 4 + j] == 0) // Ignore 0
				continue;
			if (st->first.table[i * 4 + j] != solved[i]) { // Calculate distance
				ret += abs((i - st->first.table[i * 4 + j] - 1) / board::height)
					+  abs((j - st->first.table[i * 4 + j] - 1) % board::width);
			}
		}
	}
	return ret;
}
