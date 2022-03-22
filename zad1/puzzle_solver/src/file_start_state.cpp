#include "../lib/file_start_state.h"

file_start_state::file_start_state(const std::string& path) : table(16) {
    std::ifstream file;
    file.open(path);
    if(file.is_open()) {
        file >> board::width >> board::height;
        board::width -= '0';
        board::height -= '0';
        board::len = board::width * board::height;
        uint8_t* cursor = table.data();
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

state file_start_state::getState() {
    board::init_same();
    board b = board(table);
    // issue: after return is called board destructor, which deallocates table.
    op_path p(0);
    return {b, p};
}

