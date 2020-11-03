#include <stdlib.h>
#include "../include/localdb.h"
#include "vendor/unity.h"

/* open the database connection */
void setUp(void) {}

/* close the databse connection */
void tearDown(void) {}

/* database file is created */
void test_basic_connection(void) {
    int c;
    c = dbconnect();
    TEST_ASSERT_EQUAL(c, EXIT_SUCCESS);
}

int main(void) {
    UnityBegin("test/test_localdb.c");

    RUN_TEST(test_basic_connection);
    UnityEnd();

    return EXIT_SUCCESS;
}
