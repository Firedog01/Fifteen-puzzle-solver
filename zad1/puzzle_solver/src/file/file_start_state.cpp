#include <iostream>
#include "../../lib/file/file_start_state.h"

file_start_state::file_start_state(std::string path) {
    std::ifstream file;
    file.open(path);
    if(file.is_open()) {
        file >> width >> height;
        width -= '0';
        height -= '0';
        length = width * height;
        state = new uint8_t[length];
        auto cursor = state;
        std::string buff;
        for(uint8_t i = 0; i < length; i++, cursor++) {
            file >> buff;
            *cursor = (uint8_t)stoi(buff);
        }
        file.close();
//        cursor = board;
//        for(uint8_t i = 0; i < l; i++, cursor++) {
//            std::cout << +*cursor << '\n'; // https://stackoverflow.com/questions/14644716/how-to-output-a-character-as-an-integer-through-cout
//        }
    } else {
        std::cout << "cannot open file\n";
    }
}

board* file_start_state::getState() {
    return new board(state, length);
}

file_start_state::~file_start_state() {
    delete[](state);
}
