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
    run();
    _CrtDumpMemoryLeaks();
    if (_CrtDumpMemoryLeaks() == true)
        std::cerr << "MEMORY LEAK!" << std::endl;
    return 0;
}
