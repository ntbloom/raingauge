#include <stdlib.h>
#include "../include/localdb.h"
#include "vendor/unity.h"

/* open the database connection */
void setUp(void) {}

/* close the databse connection */
void tearDown(void) {}

/* database file is created */
void test_basic_connection(void) {
    sqlite3 *db;
    db = dbconnect(LOCALDB);
    TEST_ASSERT_NOT_NULL(db);
}

int main(void) {
    UnityBegin("test/test_localdb.c");

    RUN_TEST(test_basic_connection);
    UnityEnd();

    return EXIT_SUCCESS;
}
