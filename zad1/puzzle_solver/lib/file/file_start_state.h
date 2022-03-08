#ifndef ZAD1_FILE_START_STATE_H
#define ZAD1_FILE_START_STATE_H

#include <fstream>
#include "../includes.h"

class file_start_state {
    std::ifstream file;

public:
    file_start_state(std::string file);
    board4x4 getState();
};


#endif //ZAD1_FILE_START_STATE_H
