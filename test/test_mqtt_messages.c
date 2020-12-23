#include <stdlib.h>
#include "../lib/constants.h"
#include "../lib/mqtt_messages.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

/* Can we create a basic MQTT message */
void test_timestamps(void) {
    /* for now just print debugging*/
    char *timestamp, *uptime;
    timestamp = get_timestamp();
    puts("TESTING timestamps and uptime...");

    uptime = get_uptime();
    printf("\ttimestamp = %s, uptime=%s\n ", timestamp, uptime);
    puts("");

    free(timestamp);
    free(uptime);
}

/* can we make an MQTT rain message */
void test_make_message_rain(void) {
    char *gauge, *amt;
    Message *msg;

    gauge = "bluehouse";
    amt = "0.2794";
    msg = message_rain(gauge, amt);

    puts("TESTING message_rain()...");
    printf("\ttopic=%s, payload=%s, timestamp=%s\n", msg->topic, msg->payload, msg->timestamp);
    TEST_ASSERT_EQUAL_INT(deconstruct_message(msg), EXIT_SUCCESS);
    puts("");
}

/* can we make an MQTT status message */
void test_make_message_status(void) {
    char *gauge;
    Message *msg;

    gauge = "a_different_gauge";
    msg = message_status(gauge);

    puts("TESTING message_status()...");
    printf("\ttopic=%s, payload=%s, timestamp=%s\n", msg->topic, msg->payload, msg->timestamp);
    TEST_ASSERT_EQUAL_INT(deconstruct_message(msg), EXIT_SUCCESS);
    puts("");
}

int main(void) {
    UnityBegin("test/test_mqtt_messages.c");

    RUN_TEST(test_timestamps);
    RUN_TEST(test_make_message_rain);
    RUN_TEST(test_make_message_status);
    UnityEnd();

    return EXIT_SUCCESS;
}
