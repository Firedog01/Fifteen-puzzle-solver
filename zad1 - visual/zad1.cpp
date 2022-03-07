#include <iostream>
#include "info_handler.h"
#include "extra_info.h"

int main()
{
    extra_info extraInfo;
    extraInfo.setRecursionLevel(5);
    extraInfo.getExecutionTime();
    std::cout << "Hello World!\n";
}
