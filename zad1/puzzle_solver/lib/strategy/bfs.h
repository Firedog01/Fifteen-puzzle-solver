#ifndef ZAD1_BFS_H
#define ZAD1_BFS_H

#include <queue>
#include <unordered_map>
#include "../includes.h"
#include "../info/info_bundle.h"
#include "../puzzle/board_hash.h"
#include "../puzzle/op_path.h"
#include "../puzzle/board_handler.h"

struct bfs {
    /* bfs wer 3:
        s - stan początkowy
        if s is solution:
            return success
        Q = queue
        U = set
        Q.enqueue(s)
        while !Q.isempty():
            v = Q.dequeue()
            for n in neighbours(v):
                if n is solution:
                    return success
                if !U.has(n):
                    Q.enqueue(n)
                    U.add(v)
        return failure
     */
    static op_path algorithm(state* start_state, ops::operators* order, info_bundle& info) {
        std::queue<state> q_to_process;
        std::unordered_map<board, op_path, board_hash> visited;
        uint8_t* solved_table = board_handler::getSolvedTable();
        state* cur_state;

        q_to_process.emplace(*start_state);                     /// Q.enqueue(s)
        info.statesProcessed++;
        while(!q_to_process.empty()) {                          /// while !Q.isempty():
            cur_state = &q_to_process.front();                  /// v = Q.dequeue()
            info.statesProcessed++;

            ops::operators* op = order;
            for(int i = 0; i < 4; i++, op++) {                  /// for n in neighbours(v):
                auto neighbour = board_handler::new_moved(cur_state, *op);
                if(board::same(solved_table, cur_state->first.table)) { /// if n is solution:
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
};


#endif //ZAD1_BFS_H
