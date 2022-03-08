#include <iostream>
#include "../../lib/file/file_start_state.h"

file_start_state::file_start_state(std::string path) {
    file.open(path);
    if(file.is_open()) {
        char w, k;
        file>>w>>k;
        w -= '0';
        k -= '0';
        uint8_t l = w*k;
        auto board = new uint8_t[l];
        auto cursor = board;
        std::string buff;
        for(uint8_t i = 0; i < l; i++, cursor++) {
            file >> buff;
            *cursor = (uint8_t)stoi(buff);
        }
//        cursor = board;
//        for(uint8_t i = 0; i < l; i++, cursor++) {
//            std::cout << +*cursor << '\n'; // https://stackoverflow.com/questions/14644716/how-to-output-a-character-as-an-integer-through-cout
//        }
//        if(w == k && w == 4) {
//            std::cout << "board 4x4\n";
//        }
    } else {
        std::cout << "cannot open file\n";
    }
}
