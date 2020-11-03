#include "../include/localdb.h"

sqlite3* dbconnect(const char* filename) {
    int rc;
    sqlite3* db;

    rc = sqlite3_open(filename, &db);
    if (rc) {
        fprintf(stderr, "error opening sqlite3 file at %s\n", LOCALDB);
        return NULL;
    }
    return db;
}
