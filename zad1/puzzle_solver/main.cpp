#include <iostream>
#include "lib/manager.h"

int main(int argc, char *argv[]) {
    if(argc != 6) {
        std::cout << "Incorrect number of parameters!\n"
                  << "Every call should have exactly 5 arguments.\n";
        return 1;
    }
    manager manager(argv);
    return 0;
}


