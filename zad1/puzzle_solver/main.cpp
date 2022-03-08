#include <iostream>
#include <chrono>
#include <unistd.h>
#include <iomanip>
#include "lib/info/info_bundle.h"

int main(int argc, char *argv[]) {
    info_bundle info;
    std::string strategy;
    std::string parameter;
    std::string startStateFile;
    std::string endStateFile;
    std::string extraInfoFile;

    switch(argc) {
        case 6:
            extraInfoFile = argv[5];
        case 5:
            endStateFile = argv[4];
        case 4:
            startStateFile = argv[3];
        case 3:
            parameter = argv[2];
        case 2:
            strategy = argv[1];
    }
    // argv[0] zawiera wywołanie funkcji ze ścieżką
    // w clionie można ustawić automatyczne przesyłanie parametrów do skompilowanego
    // programu w (konfiguracja kompilacji 'zad1 | Debug' > Edit Configurations...
    // ja dałem: bfs LRUD start_state.txt end_state.txt extra_info.txt
    std::cout << argc << '\n';
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
    sleep(1);
    std::cout << "Execution time: "
              << std::setprecision(3) << std::fixed
              << info.getExecutionTime() << " ms\n";
    return 0;
}
