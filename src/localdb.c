#include "localdb.h"

static char* errmsg;
static double total_ticks;

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
    char* sql;

    sql = malloc(255);
    sprintf(sql,
            "BEGIN; INSERT INTO ticks (db_time, gauge, amount) SELECT Datetime('now'), %d, "
            "mm_per_click FROM "
            "gauge WHERE id = %d; COMMIT;",
            gauge, gauge);
    rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, errmsg);
        return EXIT_FAILURE;
    }

    free(sql);
    return EXIT_SUCCESS;
}

int print_row_callback(__attribute__((unused)) void* _, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s=%s\n", azColName[i], argv[i]);
    }
    total_ticks = atof(argv[0]);
    return EXIT_SUCCESS;
}

double db_count_ticks(sqlite3* db, int gauge) {
    int rc;
    char* sql = malloc(100);
    sprintf(sql, "SELECT sum(amount) FROM ticks WHERE gauge = %d", gauge);
    rc = sqlite3_exec(db, sql, print_row_callback, 0, &errmsg);
    free(sql);

    if (rc) {
        fprintf(stderr, "SQLITE ERROR %d: %s\n", rc, errmsg);
        return -1.0;
    }
    return total_ticks;
}
