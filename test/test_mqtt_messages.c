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
    timestamp = get_timestamp();
    printf("timestamp = %s\n", timestamp);
    free(timestamp);

    up = get_uptime();
    if (up != NULL) {
        printf("uptime = %s\n", up);
    }
    free(up);
}

/* can we make an MQTT rain message */
void test_make_message_rain(void) {
    Message *msg;
    const char *gauge = "bluehouse";
    const char *amt = "0.2794";

    msg = message_rain(gauge, amt);

    printf("topic=%s, payload=%s, timestamp=%s\n", msg->topic, msg->payload, msg->timestamp);

    TEST_ASSERT_EQUAL_INT(deconstruct_message(msg), EXIT_SUCCESS);
}

int main(void) {
    UnityBegin("test/test_mqtt_messages.c");

    RUN_TEST(test_timestamps);
    RUN_TEST(test_make_message_rain);
    UnityEnd();

    return EXIT_SUCCESS;
}
