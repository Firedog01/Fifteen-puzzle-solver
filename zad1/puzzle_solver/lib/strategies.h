#ifndef ZAD1_STRATEGIES_H
#define ZAD1_STRATEGIES_H

#include <queue>
#include <unordered_map>
#include "includes.h"
#include "info/info_bundle.h"
#include "puzzle/board_handler.h"

struct strategies {
    strategies();
    ~strategies();
    uint8_t* solved_table;

    op_path bfs(state& start_state, ops::operators* order, info_bundle& info);
    op_path dfs(state& start_state, ops::operators* order, info_bundle& info);
	op_path astr(state& start_state, ops::heuristics heur, info_bundle& info);
};


#endif //ZAD1_STRATEGIES_H
