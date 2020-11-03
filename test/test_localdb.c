#include <stdlib.h>
#include "../include/localdb.h"
#include "vendor/unity.h"

/* create a database file with schema */
void setUp(void) {
    if (create_db(LOCALDB) != EXIT_SUCCESS) {
        TEST_ASSERT_EQUAL(1, 0);
    }
}

/* delete the database file */
void tearDown(void) {
    if (remove(LOCALDB) != EXIT_SUCCESS) {
        TEST_ASSERT_EQUAL(1, 0);
    }
}

/* database file is created */
void test_basic_connection(void) {
    sqlite3 *db;
    db = db_connect(LOCALDB);
    TEST_ASSERT_NOT_NULL(db);
}

int main(void) {
    UnityBegin("test/test_localdb.c");

    RUN_TEST(test_basic_connection);
    UnityEnd();

    return EXIT_SUCCESS;
}
