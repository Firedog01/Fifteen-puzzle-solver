#ifndef ZAD1_MANAGER_H
#define ZAD1_MANAGER_H

#include <algorithm>
#include <string>
#include <iomanip>
#include <iostream>
#include <queue>
#include "includes.h"
#include "file/file_start_state.h"
#include "info/info_bundle.h"
#include "puzzle/board.h"
#include "puzzle/board_handler.h"

class manager {
    info_bundle info;
    std::string strategy,
                param,
                start_state_file,
                result_file,
                extra_info_file;

    static ops::operators* getOrder(std::string s);
    static ops::heuristics getHeuristic(std::string s);

    std::string getStrPath(ops::operators * ops, uint8_t len);
    void displayBoard(uint8_t * state);

public:
    manager(std::string strategy, std::string param, std::string s_file, std::string e_file, std::string ex_file);
    manager(char** argv);

    void findSolution();
};


#endif //ZAD1_MANAGER_H
