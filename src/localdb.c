#include "../include/localdb.h"

static char* errmsg;

int create_db(const char* db_file) {
    /* define the schema */
    sqlite3* db;
    int rc;

    rc = sqlite3_open(db_file, &db);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }

    rc = sqlite3_exec(db, SCHEMA, NULL, NULL, &errmsg);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, errmsg);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    rc = sqlite3_close(db);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, sqlite3_errmsg(db));
    }
    return EXIT_SUCCESS;
}

int create_sample_gauge(sqlite3* db) {
    int rc;
    if (db == NULL) {
        fprintf(stderr, "Database is not opened\n");
        return EXIT_FAILURE;
    }
    rc = sqlite3_exec(db, NEWGAUGE, NULL, NULL, &errmsg);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, errmsg);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

sqlite3* db_connect(const char* db_file) {
    int rc, db_flags;
    sqlite3* db;

    db_flags = SQLITE_OPEN_READWRITE;

    rc = sqlite3_open_v2(db_file, &db, db_flags, NULL);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

int db_add_tick(sqlite3* db, int gauge) {
    if (db == NULL) {
        fprintf(stderr, "Database is not opened\n");
        return EXIT_FAILURE;
    }
    int rc;
    char* insert;

    insert = malloc(255);
    sprintf(insert,
            "INSERT INTO ticks (db_time, gauge, num) SELECT Datetime('now'), %d, mm_per_click FROM "
            "gauge WHERE id = %d;",
            gauge, gauge);
    printf("%s\n", insert);
    rc = sqlite3_exec(db, insert, NULL, NULL, &errmsg);
    printf("errmsg in add_tick = %s\n", errmsg);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, errmsg);
        return EXIT_FAILURE;
    }

    free(insert);
    return EXIT_SUCCESS;
}

// void db_print_ticks(sqlite3* db, int gauge) {
/*
 *
 */
//}

