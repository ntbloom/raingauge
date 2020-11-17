#include <stdlib.h>
#include "../src/localdb.h"
#include "unity.h"

/* create a database file with schema */
void setUp(void) {
    if (create_db(LOCALDB) != EXIT_SUCCESS) {
        TEST_FAIL_MESSAGE("error creating database");
    }
}

/* delete the database file */
void tearDown(void) {
    if (remove(LOCALDB) != EXIT_SUCCESS) {
        TEST_FAIL_MESSAGE("error deleting database");
    }
}

/* database file is created */
void test_basic_connection(void) {
    int prep, click, gauge;
    sqlite3 *db;

    db = db_connect(LOCALDB);
    gauge = 1;

    TEST_ASSERT_NOT_NULL_MESSAGE(db, "failure to connect to database file");
    prep = create_sample_gauge(db);
    TEST_ASSERT_EQUAL_MESSAGE(prep, EXIT_SUCCESS, "sample gauge not created");

    for (int i = 0; i < 10; i++) {
        click = db_add_tick(db, gauge);
        TEST_ASSERT_EQUAL_MESSAGE(click, EXIT_SUCCESS, "tick not added to database");
    }
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2.794, db_count_ticks(db, gauge));

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, sqlite3_close(db));
}

int main(void) {
    UnityBegin("test/test_localdb.c");

    RUN_TEST(test_basic_connection);
    UnityEnd();

    return EXIT_SUCCESS;
}
