#include "../../lib/file/file_start_state.h"


file_start_state::file_start_state(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(file.is_open()) {
        file >> board::width >> board::height;
        board::width -= '0';
        board::height -= '0';
        board::len = board::width * board::height;
        state = new uint8_t[board::len];
        auto cursor = state;
        std::string buff;
        for(uint8_t i = 0; i < board::len; i++, cursor++) {
            file >> buff;
            *cursor = (uint8_t)stoi(buff);
        }
        file.close();
    } else {
        std::cout << "cannot open file\n";
    }
}

board* file_start_state::getState() {
    return new board(state);
}

file_start_state::~file_start_state() {
    delete[](state);
}

