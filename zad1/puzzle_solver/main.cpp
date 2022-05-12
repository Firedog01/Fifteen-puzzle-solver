#include <iostream>
#include "lib/manager.h"
//#include "lib/puzzle/heuristics.h"


int main(int argc, char *argv[]) {
    /*
	op_path p;
	state b(std::vector<uint8_t>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 14, 0}), p);
    uint8_t sol[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    board::width = 4;
    board::height = 4;
	std::cout << heuristics::manhattan(&b, sol);
	return 0;*/

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


