#include <iostream>
#include <chrono>
#include <unistd.h>
#include <iomanip>
#include "lib/info/info_bundle.h"

int main(int argc, char *argv[]) {
    info_bundle info;
    sleep(1);
    std::cout << "Execution time: "
              << std::setprecision(3) << std::fixed
              << info.getExecutionTime() << " ms\n";
    return 0;
}
