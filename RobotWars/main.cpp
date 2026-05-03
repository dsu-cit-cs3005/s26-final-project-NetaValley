#include "Arena.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./RobotWarz config.txt\n";
        return 1;
    }

    Arena arena;

    if (!arena.load_config(argv[1])) {
        return 1;
    }

    arena.setup();
    arena.run();

    return 0;
}