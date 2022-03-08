#include <iostream>
#include "../lib/manager.h"


manager::manager(char **argv) : info() {
    std::string strategy(argv[1]);
    file_start_state startStateHandler(argv[3]);
    board* state = startStateHandler.getState();
    if(strategy == "bfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "dfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(argv[2]);
    }
    delete(state);

    double execTime = info.getExecutionTime();
    std::cout << execTime << '\n';
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
