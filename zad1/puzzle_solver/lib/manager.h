//
// Created by janru on 08.03.2022.
//

#ifndef ZAD1_MANAGER_H
#define ZAD1_MANAGER_H

#include <algorithm>
#include <string>
#include "includes.h"
#include "file/file_start_state.h"
#include "info/info_bundle.h"
#include "puzzle/board.h"

class manager {
    info_bundle info;

    static ops::operators* getOrder(std::string s);
    static ops::heuristics getHeuristic(std::string s);

public:
    manager(char** argv);
};


#endif //ZAD1_MANAGER_H
