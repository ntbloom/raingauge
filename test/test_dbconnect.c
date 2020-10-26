#include <stdlib.h>
#include "../src/dbconnect.h"
#include "vendor/unity.h"

#define GAUGE 1
#define CONNINFO "dbname=local connect_timeout=10"
#define DELTA 0.00001

static PGconn* CONN;

/* clear everything from the clicks table */
void clear_clicks(void) {
    const char* setup = "DELETE FROM ticks;";
    PGresult* res = PQexec(CONN, setup);
    ExecStatusType status = PQresultStatus(res);
    if (status != PGRES_COMMAND_OK) {
        fprintf(stderr, "error in prep: %s", PQresStatus(status));
    }
    PQclear(res);
}

/* open the database connection */
void setUp(void) {
    CONN = dbconnect(CONNINFO);
    clear_clicks();
}

/* close the databse connection */
void tearDown(void) {
    clear_clicks();
    PQfinish(CONN);
}

/* check that the connection is valid */
void test_basic_connection(void) { TEST_ASSERT_NOT_NULL_MESSAGE(CONN, "bad connection"); }

/* basic select from the database, more for understanding the library than testing
 * anything */
void test_select(void) {
    int i;
    PGresult* res;
    const char* select;

    select = "SELECT 42;";
    res = PQexec(CONN, select);
    TEST_ASSERT_EQUAL_INT_MESSAGE(PGRES_TUPLES_OK, PQresultStatus(res), "failure at SELECT");
    i = atoi(PQgetvalue(res, 0, 0));
    TEST_ASSERT_EQUAL_INT_MESSAGE(42, i, "incorrect number returned");

    PQclear(res);
}

/* test a click event */
void test_add_tick(void) {
    double actual, expected;
    int set, i, count;

    count = 20;

    for (i = 0; i < count; i++) {
        set = add_tick(CONN, GAUGE);
        TEST_ASSERT_EQUAL_INT_MESSAGE(set, EXIT_SUCCESS, "failure at add_tick()");
    }
    actual = all_ticks(CONN, GAUGE);
    TEST_ASSERT_MESSAGE(actual > 0, "error in all_ticks() query");
    expected = count * 0.2794;
    TEST_ASSERT_MESSAGE((actual - expected) < DELTA || (expected - actual) < DELTA,
                        "incorrect value from all_ticks()");
}

int main(void) {
    UnityBegin("test/test_dbconnect.c");

    RUN_TEST(test_basic_connection);
    RUN_TEST(test_select);
    RUN_TEST(test_add_tick);
    UnityEnd();

    return EXIT_SUCCESS;
}
