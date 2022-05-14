#include "../../lib/puzzle/heuristics.h"

// Are numbers in place
uint16_t heuristics::hamming(state* st, const uint8_t *solved) {
	uint16_t ret = 0;
    auto sti = st->first.table.begin();
    const uint8_t *soli = solved;
	for(; sti < st->first.table.end(); sti++, soli++) {
		if (*sti == 0) // Ignore 0
			continue;
		ret += (*sti != *soli);
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
    auto sti = st->first.table.begin();
    const uint8_t* soli = solved;
    for(; sti != st->first.table.end() - 2; sti++, soli++) {
        if (*sti == 0) // Ignore 0
            continue;
        if (*sti != *soli) { // Calculate distance
            ret += abs((*sti - 1) / board::height - (*soli - 1) / board::height);
            ret += abs((*sti - 1) % board::width - (*soli - 1) % board::height);
        }
    }
    if (*++sti != 0) { // Treat last field in a special way
        ret += (board::len - *sti) / board::height;
        ret += (board::len - *sti) % board::width;
    }
	return ret;
}
