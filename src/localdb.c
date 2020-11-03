#include "../include/localdb.h"

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

// int db_add_click(sqlite3* db) {
/* pass
 *
 */

//    return -1;
//}

