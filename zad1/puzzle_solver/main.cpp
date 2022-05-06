#include <iostream>
#include "lib/manager.h"
//#include "lib/puzzle/heuristics.h"


int main(int argc, char *argv[]) {
    /* UNCOMMENT TO TEST HAMMING
    state b(std::vector<uint8_t>({1 , 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}), op_path());
    std::cout << heuristics::hamming(&b, board_handler::new_solved_table());
    */
    if(argc != 6) {
        std::cout << "Incorrect number of parameters!\n"
                  << "Every call should have exactly 5 arguments.\n";
        std::ofstream file("../../output_main.txt");
        file << "incorrect number of args";
        return 1;
    }
	manager manager(argv);
    manager.find_solution();
    return 0;
}


