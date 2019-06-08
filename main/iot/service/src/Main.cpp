#include "Service.h"
#include "Database.h"

/**
 * Service to run in the background
 * @return
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    Database *db = Database::getInstance();
    db->setConfigFilePath(argv[1]);
    startService();
    return 0;
}
