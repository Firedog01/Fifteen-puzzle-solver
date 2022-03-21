#include "../lib/manager.h"


manager::manager(char **argv) : info(), strategy(argv[1]), param(argv[2]), start_state_file(argv[3]),
                                result_file(argv[4]), extra_info_file(argv[5]) {}


manager::manager(std::string strategy, std::string param, std::string s_file, std::string e_file, std::string ex_file):
        info(), strategy(std::move(strategy)), param(std::move(param)), start_state_file(std::move(s_file)),
        result_file(std::move(e_file)), extra_info_file(std::move(ex_file)) {}

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



void manager::findSolution() {
    file_start_state startStateHandler(start_state_file);
    state start_state = startStateHandler.getState();
//    board_handler::displayBoard(start_state.first);
    op_path solution;


    if(strategy == "bfs") {
        ops::operators* order = getOrder(param); // length: [4]
        solution = bfs::algorithm(start_state, order, info);
        if (solution.len != -1) {
            // solution found!
        }
    } else if(strategy == "dfs") {
        auto order = getOrder(param);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(param);
    }
    double execTime = info.getExecutionTime();
//    std::cout << execTime << '\n';

    // result file
    std::ofstream solutionFile(result_file);
    solutionFile << solution.len << "\n";
    if(solution.len != -1) {
        solutionFile << solution.toString();
    }
    solutionFile.close();

    // extra info file
    std::ofstream infoFile(extra_info_file);
    infoFile
            << solution.len << '\n'
             << info.statesProcessed << '\n'
             << info.statesVisited << '\n'
             << info.maxDepth << '\n'
             << std::setprecision(3) << std::fixed << execTime << '\n';
    infoFile.close();
}
