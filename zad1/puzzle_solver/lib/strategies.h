#ifndef ZAD1_STRATEGIES_H
#define ZAD1_STRATEGIES_H

#include <queue>
#include <stack>
#include <unordered_map>
#include "includes.h"
#include "info/info_bundle.h"
#include "puzzle/board_handler.h"
#include "../lib/strategies.h"
#include "../lib/puzzle/state_astr.h"
#include "../lib/puzzle/astr_compare.h"

#define DFS_MAX_DEPTH 25

struct strategies {
    strategies();
    ~strategies();
    uint8_t* solved_table;

	static uint16_t (*heuristic)(state* st, uint8_t* solved);
    op_path bfs(state& start_state, ops::operators* order, info_bundle& info) const;
    op_path dfs(state& start_state, ops::operators* order, info_bundle& info) const;
	op_path astr(state& start_state, ops::heuristics* heur, info_bundle& info) const;
};


#endif //ZAD1_STRATEGIES_H
