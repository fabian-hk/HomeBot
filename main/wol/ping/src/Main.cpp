#include "Ping.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    printf("%i", sendPing(argv[1], atoi(argv[2])));

    return 0;
}

