#include <stdlib.h>
#include "../lib/constants.h"
#include "../lib/mqtt_messages.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

/* Can we create a basic MQTT message */
void test_create_gauge(void) {
    /* for now just print debugging
     *
     */
    char* timestamp = make_timestamp();
    printf("timestamp = %s\n", timestamp);
    free(timestamp);
}

int main(void) {
    UnityBegin("test/test_mqtt_messages.c");

    RUN_TEST(test_create_gauge);
    UnityEnd();

    return EXIT_SUCCESS;
}
