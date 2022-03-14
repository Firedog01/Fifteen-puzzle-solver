#include "../lib/manager.h"


manager::manager(const char **argv) : info() {
    std::string strategy(argv[1]);
    file_start_state startStateHandler(argv[3]);

    board* start_state = startStateHandler.getState();
    uint8_t* solved_table = board_handler::getSolvedTable();
    bool (*same)(uint8_t* first, uint8_t* second);
    same = &board_handler::sameMod8;

//    if(board::len == 16) {
//        same = &board_handler::same16;
//    } else if(board::len % 8 == 0) {
//        same = &board_handler::sameMod8;
//    } else if(board::len % 4 == 0) {
//        same = &board_handler::sameMod4;
//    } else {
//        same = &board_handler::sameAny;
//    }

    ops::operators* solution = nullptr;
    int solution_len = -1;
    int states_processed = 0;
    int states_visited = 0;


    if(strategy == "bfs") {
        ops::operators* order = getOrder(argv[2]); // ops::operators[4]
        std::queue<board*> q_to_process;
        std::vector<board*> visited;
        board* cur_state;

        q_to_process.emplace(start_state);
        states_processed++;

        while(!q_to_process.empty()) {
            cur_state = q_to_process.front();
            states_processed++;

            if(same(solved_table, cur_state->table)) {
                // solution found!
//                std::cout << "solution found\n";
                solution = cur_state->path;
                solution_len = cur_state->pathLen;
                break;
            } else {
                ops::operators* op = order;
                for(int i = 0; i < 4; i++, op++) {
                    auto new_board = board_handler::createMoved(cur_state, *op);
                    if(new_board == nullptr) {
                        continue;
                    }
                    auto found = std::find_if(
                            visited.begin(),
                            visited.end(),
                            [same, new_board](board* i) {
                                return same(i->table, new_board->table);
                            });
                    if(found == visited.end()) { // not found
                        q_to_process.push(new_board);
                    } else {
                        delete(new_board);
                    }
                }
                states_visited += 4;
            }
            visited.push_back(cur_state);
            q_to_process.pop();
        }

    } else if(strategy == "dfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(argv[2]);
    }
    delete(start_state);
    auto execTime = info.getExecutionTime();
//    std::cout << execTime << '\n';

    std::ofstream solutionFile(argv[4]);
    solutionFile << solution_len << "\n";
    if(solution != nullptr) {
        solutionFile << getStrPath(solution, solution_len);
    }
    solutionFile.close();

    std::ofstream infoFile(argv[5]);
    infoFile
//             << solution_len << '\n'
//             << states_visited << '\n'
//             << states_processed << '\n'
//             << info.getMaxDepth() << '\n'
             << std::setprecision(3) << std::fixed << execTime << '\n';
    infoFile.close();

}

/**
 * Creates new table that needs to be deleted.
 *
 * @param s input string
 * @return table of operators, table_len exactly 4 or nullptr
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
                    throw std::logic_error("illegal operators, must be permutation of L, R, U, D");
            }
        }
        return order;
    }
    throw std::logic_error("incorrect operators count");
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

std::string manager::getStrPath(ops::operators * ops, uint8_t len) {
    std::stringstream ss;
    for(int i = 0; i < len; i++, ops++) {
        switch(*ops) {
            case ops::L:
                ss << "L";
                break;
            case ops::R:
                ss << "R";
                break;
            case ops::D:
                ss << "D";
                break;
            case ops::U:
                ss << "U";
                break;
        }
    }
    ss << "\n";
    return ss.str();
}

void manager::displayBoard(uint8_t *state) {
    for(int i = 0; i < board::len; i++) {
        std::cout << +state[i] << " ";
        if(i % 4 == 3)
            std::cout << '\n';
    }
}
