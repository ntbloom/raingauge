/*
   test_sysfs_gpio.c
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/sysfs_gpio.h"
#include "vendor/unity.h"

#define RUN_TEST_NO_SETUP(testfunc) \
    UNITY_NEW_TEST(#testfunc)       \
    if (TEST_PROTECT()) {           \
        testfunc();                 \
    }                               \
    UnityConcludeTest();

struct Pin const GPIO18 = {.num = "18",
                           .fdesc = "/sys/class/gpio/gpio18",
                           .direction = "/sys/class/gpio/gpio18/direction",
                           .value = "/sys/class/gpio/gpio18/value"};

void setUp(void) {
    // export a pin where it previously did not exist
    create_pin(GPIO18);
    set_direction(GPIO18, OUT);
}
void tearDown(void) {
    // unexport pin at the end of the tests
    remove_pin(GPIO18);
}

void test_export_unexport_pin(void) {
    /* can we turn on and turn off a pin */

    // start first test from preconditions
    const char* msg1 = "pin already exists";
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg1);

    // turn it on
    create_pin(GPIO18);
    const char* msg2 = "pin not created";
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(GPIO18.fdesc, F_OK), msg2);

    // turn it back off again
    remove_pin(GPIO18);
    const char* msg3 = "pin was not unexported";
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg3);
}

void test_pin_direction(void) {
    /* check setting the direction out and in and out */
    const char* msg1 = "pin is set to 'in'";
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(OUT, get_direction(GPIO18), strlen(OUT), msg1);

    set_direction(GPIO18, IN);
    const char* msg2 = "pin is set to 'out'";
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(IN, get_direction(GPIO18), strlen(IN), msg2);

    set_direction(GPIO18, OUT);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(OUT, get_direction(GPIO18), strlen(OUT), msg1);
}

void test_pin_value(void) {
    /* on a pin set to out, can we turn it to low and high */
    const char* msg1 = "pin is set to '0'";
    set_value(GPIO18, HIGH);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("1", get_value(GPIO18), strlen(HIGH), msg1);
}

void test_setup(void) {
    // empty test for testing setup preconditions
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void) {
    UnityBegin("test/test_sysfs_gpio.c");

    RUN_TEST(test_setup);
    RUN_TEST_NO_SETUP(test_export_unexport_pin);
    RUN_TEST(test_pin_direction);

    UnityEnd();

    return EXIT_SUCCESS;
}
