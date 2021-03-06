#include <iostream>
#include "lib/manager.h"


int main(int argc, char *argv[]) {
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


