#include <stdlib.h>
#include "../lib/constants.h"
#include "../lib/mqtt_messages.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

/* Can we create a basic MQTT message */
void test_timestamps(void) {
    /* for now just print debugging*/
    char *timestamp, *up;
    timestamp = make_timestamp(ISO8601_LEN, ISO8601);
    printf("timestamp = %s\n", timestamp);
    free(timestamp);

    up = get_uptime();
    if (up != NULL) {
        printf("uptime = %s\n", up);
    }
    free(up);
}

int main(void) {
    UnityBegin("test/test_mqtt_messages.c");

    RUN_TEST(test_timestamps);
    UnityEnd();

    return EXIT_SUCCESS;
}
