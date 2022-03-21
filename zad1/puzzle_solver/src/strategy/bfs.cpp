#include "../../lib/strategy/bfs.h"


op_path bfs::algorithm(const state& start_state, ops::operators *order, info_bundle &info) {
    board::init_same();
    std::queue<state> q_to_process;
    std::unordered_map<board, op_path, board_hash> visited;
    uint8_t* solved_table = board_handler::getSolvedTable();
    state* cur_state;
    board_handler::displayBoard(start_state.first.table);

    q_to_process.emplace(start_state);                     /// Q.enqueue(s)
    info.statesProcessed++;
    while(!q_to_process.empty()) {                          /// while !Q.isempty():
        cur_state = &q_to_process.front();                  /// v = Q.dequeue()
        board_handler::displayBoard(cur_state->first.table);
        info.statesProcessed++;

        ops::operators* op = order;
        for(int i = 0; i < 4; i++, op++) {                  /// for n in neighbours(v):
            auto neighbour = board_handler::new_moved(cur_state, *op);
            if(board::same(solved_table, cur_state->first.table.data())) { /// if n is solution:
                // solution found!
                std::cout << "solution found\n";
                op_path solution = neighbour->second;
                delete neighbour;
                return solution;
            }

            /// if !U.has(n):
            ///     Q.enqueue(n)
            ///     U.add(v)

            // returns std::pair<iterator, bool>
            // it.second informs whether insertion was successful
            auto it = visited.insert(*neighbour);
            if(it.second) {
                q_to_process.push(*neighbour); // copy is created
            }
            delete neighbour;
        }
        q_to_process.pop();
    }
    return {-1};
}
