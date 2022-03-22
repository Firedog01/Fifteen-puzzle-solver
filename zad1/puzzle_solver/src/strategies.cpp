#include "../lib/strategies.h"

strategies::strategies() {
    board::init_same();
    solved_table = board_handler::new_solved_table(); // to modify solved state pass different function

}


strategies::~strategies() {
    delete[](solved_table);
}

op_path strategies::bfs(state &start_state, ops::operators *order, info_bundle &info) {
    std::queue<state> open_states;
    std::unordered_map<board, op_path, board_hash> processed_states;
    state* cur_state;   // for iteration
    open_states.emplace(start_state);                     /// Q.enqueue(s)

    info.processed++;
    info.visited++;

    while(!open_states.empty()) {                          /// while !Q.isempty():
        cur_state = &open_states.front();                  /// v = Q.dequeue()

        ops::operators* op = order;
        for(int i = 0; i < 4; i++, op++) {                  /// for n in neighbours(v):
            auto neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
            if(neighbour == nullptr) { // illegal move or trivial(for example RL or UD)
                continue;
            }
            info.set_max_depth(neighbour->second.len);
            if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
                // solution found!
                op_path solution = neighbour->second;
                delete neighbour;
                return solution;
            }

            /// if !U.has(n):
            ///     Q.enqueue(n)
            ///     U.add(v)
            auto it = processed_states.insert(*neighbour);
            // it.second informs whether insertion was successful
            // processed_states.insert returns std::pair<iterator, bool>
            if(it.second) {
                open_states.push(*neighbour); // copy is created
                info.visited++;
            }
            delete neighbour;
        }
        info.processed++;
        open_states.pop();
    }
    return {-1};
}

op_path strategies::dfs(state &start_state, ops::operators *order, info_bundle &info) {
    if(board::same(start_state.first.table.data(), solved_table)) {

    }
}

