#ifndef ZAD1_FILE_START_STATE_H
#define ZAD1_FILE_START_STATE_H

#include <fstream>
#include <utility>
#include "includes.h"
#include "puzzle/board_handler.h"

// max rozmiar 255x255, chyba starczy
class file_start_state {
    std::vector<uint8_t> table;

public:
    file_start_state(const std::string& file);
    state getState();
};


#endif //ZAD1_FILE_START_STATE_H
