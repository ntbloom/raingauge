#include "../lib/constants.h"
#include "../lib/mqtt_messages.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

/* Can we create a basic MQTT message */
void test_create_gauge(void) {}

int main(void) {
    UnityBegin("test/test_mqtt_messages.c");

    RUN_TEST(test_create_gauge);
    UnityEnd();

    return EXIT_SUCCESS;
}
