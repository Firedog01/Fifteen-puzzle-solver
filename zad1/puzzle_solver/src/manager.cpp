#include <iostream>
#include "../lib/manager.h"
#include "../lib/puzzle/board_handler.h"


manager::manager(char **argv) : info() {
    std::string strategy(argv[1]);
    file_start_state startStateHandler(argv[3]);

    board* start_state = startStateHandler.getState();
    uint16_t table_length = startStateHandler.getLength();
    uint8_t* solved_table = board_handler::getSolvedTable(table_length);

    if(strategy == "bfs") {
        ops::operators* order = getOrder(argv[2]); // ops::operators[4]
        std::queue<board*> q_to_process; // ueue is silent
        std::vector<board*> visited; //
        q_to_process.emplace(start_state);

        // same is function pointer. There are different functions depending on table_length
        bool (*same)(uint8_t* solved_table, uint8_t* current_table, uint8_t table_length);
        if(table_length % 8 == 0) {
            same = &board_handler::sameMod16;
        } else if(table_length % 4 == 0) {
            same = &board_handler::sameMod4;
        } else {
            same = &board_handler::sameAny;
        }

        while(true) {
            if(q_to_process.empty()) {
                std::cout << "no solution found!\n";
                // todo
                break;
            }
            board* cur_state = q_to_process.front();
            q_to_process.pop();
            if(same(solved_table, cur_state->table, table_length)) {
                std::cout << "solution found!\n";
                // todo
                break;
            } else {
                ops::operators* op = order;
                for(int i = 0; i < 4; i++, op++) {
                    auto new_board_ptr = board_handler::createMoved(cur_state, *op);
                    q_to_process.push(new_board_ptr);
                }
            }
        }


    } else if(strategy == "dfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(argv[2]);
    }
    delete(start_state);
    auto execTime = info.getExecutionTime();
    std::cout << execTime << '\n';

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
