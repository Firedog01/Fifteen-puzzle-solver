#include "../../lib/file/file_start_state.h"
#include "../../lib/puzzle/op_path.h"


file_start_state::file_start_state(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(file.is_open()) {
        file >> board::width >> board::height;
        board::width -= '0';
        board::height -= '0';
        board::len = board::width * board::height;
        table = new uint8_t[board::len];
        auto cursor = table;
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

state* file_start_state::getState() {
    board::init_same();
    board b = board(table);
    op_path p;
    return new std::pair(b, p);
}

file_start_state::~file_start_state() {
    delete[](table);
}

