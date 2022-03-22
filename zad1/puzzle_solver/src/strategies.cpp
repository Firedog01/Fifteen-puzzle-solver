#include "../lib/strategies.h"

op_path strategies::bfs(state &start_state, ops::operators *order, info_bundle &info) {
    board::init_same();
    std::queue<state> open_states;
    std::unordered_map<board, op_path, board_hash> processed_states;

    uint8_t* solved_table = board_handler::getSolvedTable(); // to modify solved state pass different function
    state* cur_state;   // for iteration
    open_states.emplace(start_state);                     /// Q.enqueue(s)
    info.statesProcessed++;
    info.statesVisited++;

    while(!open_states.empty()) {                          /// while !Q.isempty():
        cur_state = &open_states.front();                  /// v = Q.dequeue()

        ops::operators* op = order;
        for(int i = 0; i < 4; i++, op++) {                  /// for n in neighbours(v):
            auto neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
            if(neighbour == nullptr) { // illegal move or trivial(for example RL or UD)
                continue;
            }
            info.setMaxDepth(neighbour->second.len);
            if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
                // solution found!
                op_path solution = neighbour->second;
                delete neighbour;
                return solution;
            }

            /// if !U.has(n):
            ///     Q.enqueue(n)
            ///     U.add(v)
            auto it = processed_states.insert(*neighbour);   // it.second informs whether insertion was successful
            // processed_states.insert returns std::pair<iterator, bool>
            if(it.second) {
                open_states.push(*neighbour); // copy is created
                info.statesVisited++;
            }
            delete neighbour;
        }
        info.statesProcessed++;
        open_states.pop();
    }
    return {-1};
}
