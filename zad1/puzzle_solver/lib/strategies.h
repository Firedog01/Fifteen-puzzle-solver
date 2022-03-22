#ifndef ZAD1_STRATEGIES_H
#define ZAD1_STRATEGIES_H

#include <queue>
#include <unordered_map>
#include "includes.h"
#include "info/info_bundle.h"
#include "puzzle/board_handler.h"

struct strategies {
    static op_path bfs(state& start_state, ops::operators* order, info_bundle& info);
};


#endif //ZAD1_STRATEGIES_H
