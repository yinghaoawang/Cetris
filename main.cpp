#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "Cetris/Runner.h"

void run() {
    Cetris::Runner runner;
    runner.run();
}

int main() {
    std::srand(std::time(nullptr));
    run();
    _CrtDumpMemoryLeaks();
    if (_CrtDumpMemoryLeaks() == true)
        std::cerr << "MEMORY LEAK!" << std::endl;
    else
        std::cout << "No memory leaks detected.";
    return 0;
}
