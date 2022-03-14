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

    static ops::operators* getOrder(std::string s);
    static ops::heuristics getHeuristic(std::string s);

    std::string getStrPath(ops::operators * ops, uint8_t len);
    void displayBoard(uint8_t * state);

public:
    manager(const char** argv);
};


#endif //ZAD1_MANAGER_H
