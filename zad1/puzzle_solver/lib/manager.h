#ifndef ZAD1_MANAGER_H
#define ZAD1_MANAGER_H

#include <iomanip>
#include "file_start_state.h"
#include "info/info_bundle.h"
#include "strategies.h"

class manager {
    info_bundle info;
    std::string strategy,
                param,
                start_state_file,
                result_file,
                extra_info_file;

    static ops::operators* get_order(std::string s);
    static ops::heuristics get_heuristic(std::string s);


public:
    manager(std::string strategy, std::string param, std::string s_file, std::string r_file, std::string ex_file);
    manager(char** argv);

    void find_solution();
};


#endif //ZAD1_MANAGER_H
