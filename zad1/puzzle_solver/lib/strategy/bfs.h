#ifndef ZAD1_BFS_H
#define ZAD1_BFS_H

#include <queue>
#include <unordered_map>
#include "../includes.h"
#include "../info/info_bundle.h"
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
    static op_path algorithm(const state& start_state, ops::operators* order, info_bundle& info);

    static void displayBoard(uint8_t * state);
};


#endif //ZAD1_BFS_H
