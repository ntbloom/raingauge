#include "../include/localdb.h"

#define LOCALDB "/home/pi/rain/local.db"

int dbconnect(sqlite3 *db) {
    int rc;

    rc = sqlite3_open(LOCALDB, &db);
    if (rc) {
        fprintf(stderr, "error opening sqlite3 file at %s\n", LOCALDB);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
