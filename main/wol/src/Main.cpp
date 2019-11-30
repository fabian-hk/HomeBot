#include <iostream>

#include "../../utils/Ping.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::cout << sendPing(argv[1], atoi(argv[2]));

    return 0;
}

