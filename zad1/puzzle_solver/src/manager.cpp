#include <iostream>
#include <iomanip>
#include "../lib/manager.h"
#include "../lib/puzzle/board_handler.h"


manager::manager(char **argv) : info() {
    std::string strategy(argv[1]);
    file_start_state startStateHandler(argv[3]);
    board* state = startStateHandler.getState();

    // creating solvedMod4 state for comparisons
    auto solved_board = new uint8_t[state->length];
    auto sb_ptr = solved_board;
    uint8_t* field_ptr = state->begin;
    for(uint8_t i = 0; i < state->length; i++, field_ptr++, sb_ptr++) {
        *sb_ptr = *field_ptr;
    }


    if(strategy == "bfs") {
        auto order = getOrder(argv[2]);
        uint16_t i = 0;
        if(state->length == 16) {
            while(board_handler::notSolved16(solved_board, state->begin)) {
                ops::operators oper = order[i & 0b11]; // mod 4
                board_handler::move(state, oper);

                i++;
            }
        } else if(state->length % 4 == 0) {
            while(board_handler::notSolvedMod4(solved_board, state->begin, state->length)) {
                ops::operators oper = order[i & 0b11];
            }
        } else {
            while(board_handler::notSolvedAny(solved_board, state->begin, state->length)) {
                ops::operators oper = order[i & 0b11];
            }
        }


    } else if(strategy == "dfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(argv[2]);
    }
    delete(state);
    auto execTime = info.getExecutionTime();

    std::ofstream solutionFile(argv[4]);

    solutionFile.close();

    std::ofstream infoFile(argv[5]);
    infoFile << info.getLength() << '\n'
             << info.getStatesVisited() << '\n'
             << info.getStatesProcessed() << '\n'
             << info.getMaxDepth() << '\n'
             << std::setprecision(3) << std::fixed << execTime << '\n';
    infoFile.close();

}

/**
 * Creates new table that needs to be deleted.
 *
 * @param s input string
 * @return table of operators, length exactly 4 or nullptr
 */
ops::operators* manager::getOrder(std::string s) {
    if(s.size() == 4) {
        auto order = new ops::operators[4];
        for(int i = 0; i < 4; i++) {
            switch(s[i]) {
                case 'L':
                case 'l':
                    order[i] = ops::L;
                    break;
                case 'R':
                case 'r':
                    order[i] = ops::R;
                    break;
                case 'U':
                case 'u':
                    order[i] = ops::U;
                    break;
                case 'D':
                case 'd':
                    order[i] = ops::D;
                    break;
                default:
                    delete[](order);
                    return nullptr;
            }
        }
        return order;
    }
    return nullptr;
}

ops::heuristics manager::getHeuristic(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s == "hamm") {
        return ops::hamm;
    }
    if(s == "manh") {
        return ops::manh;
    }
    return ops::error;
}
