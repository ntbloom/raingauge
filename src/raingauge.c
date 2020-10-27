#include "../include/raingauge.h"

#define PIN_NUM 25
#define CONNINFO "dbname=local connect_timeout=10"

static Pin* PIN;
static PGconn* CONN;

int start(void) {
    short prep;

    PIN = construct_pin(PIN_NUM);
    prep = write_to_file(PIN->direc, "in") | write_to_file(PIN->edge, "rising") |
           write_to_file(PIN->active_low, "1");
    if (prep != EXIT_SUCCESS) {
        perror("error setting up pin");
        return EXIT_FAILURE;
    }

    CONN = dbconnect(CONNINFO);
    if (CONN == NULL) {
        perror("bad database connection");
        return EXIT_FAILURE;
    }
    if (poll_loop(PIN->value, 10) != EXIT_SUCCESS) {
        perror("bad poll");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int stop(void) {
    /* TODO: end the infinite poll thread */
    PQfinish(CONN);
    deconstruct_pin(PIN);
    return EXIT_SUCCESS;
}

int main(void) {
    int begin, finish;
    begin = start();
    finish = stop();
    return begin | finish;
}
