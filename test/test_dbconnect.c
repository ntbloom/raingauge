#include <stdlib.h>
#include "../src/dbconnect.h"
#include "vendor/unity.h"

void setUp(void) { /* pass */
}
void tearDown(void) { /* pass */
}
void test_basic_connection(void) {
    const char* conninfo = "host=localhost port=5432 dbname=local connect_timeout=10";
    PGconn* conn = dbconnect(conninfo);
    TEST_ASSERT_NOT_NULL_MESSAGE(conn, "bad connection");
}

int main(void) {
    UnityBegin("test/test_sysfs.c");

    RUN_TEST(test_basic_connection);
    UnityEnd();

    return EXIT_SUCCESS;
}
