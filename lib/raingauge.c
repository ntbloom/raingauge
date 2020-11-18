#include "raingauge.h"

#define CONNINFO "dbname=local connect_timeout=10"

static Pin* PIN;

int start(void) {
    short prep;

    PIN = construct_pin(GAUGE_RX);
    prep = write_to_file(PIN->direc, "in") | write_to_file(PIN->edge, "rising") |
           write_to_file(PIN->active_low, "1");
    if (prep != EXIT_SUCCESS) {
        fprintf(stderr, "error setting up pin %d\n", GAUGE_RX);
        return EXIT_FAILURE;
    }

    /* TODO: export other pins, connect to database
     * TODO: start poll loops
     *
     */

    return EXIT_SUCCESS;
}

int stop(void) {
    /* TODO: end the infinite poll thread
     *
     *
     *
     */

    return EXIT_SUCCESS;
}

