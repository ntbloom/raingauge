#include "../include/localdb.h"

int create_db(const char* db_file) {
    /* define the schema */

    /* put it in the file */
    printf("%s\n", db_file);
    return EXIT_SUCCESS;
}

sqlite3* db_connect(const char* filename) {
    int rc, db_flags;
    sqlite3* db;

    db_flags = SQLITE_OPEN_READWRITE;

    rc = sqlite3_open_v2(filename, &db, db_flags, NULL);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

