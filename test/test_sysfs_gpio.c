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

Pin const GPIO18 = {.num = "18",
                    .fdesc = "/sys/class/gpio/gpio18",
                    .fdirection = "/sys/class/gpio/gpio18/direction",
                    .fvalue = "/sys/class/gpio/gpio18/value"};

void setUp(void) {
    // export a pin where it previously did not exist
    export_pin(GPIO18);
    set_direction(GPIO18, OUT);
}
void tearDown(void) {
    // unexport pin at the end of the tests
    unexport_pin(GPIO18);
}

void test_setup(void) {
    /* empty test for testing setup preconditions */
    TEST_ASSERT_EQUAL_INT(1, 1);
}
void test_export_unexport_pin(void) {
    /* can we turn on and turn off a pin */

    const char* msg1 = "pin already exists";
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg1);

    // turn it on
    export_pin(GPIO18);
    const char* msg2 = "pin not created";
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(GPIO18.fdesc, F_OK), msg2);

    // turn it back off again
    unexport_pin(GPIO18);
    const char* msg3 = "pin was not unexported";
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg3);
}

void test_pin_direction(void) {
    /* check setting the direction out and in and out */

    // start first test from preconditions, set to out
    const char* msg1 = "pin is set to 'in'";
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(OUT, get_direction(GPIO18), strlen(OUT), msg1);

    // set it in
    set_direction(GPIO18, IN);
    const char* msg2 = "pin is set to 'out'";
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(IN, get_direction(GPIO18), strlen(IN), msg2);

    // set it out again
    set_direction(GPIO18, OUT);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(OUT, get_direction(GPIO18), strlen(OUT), msg1);
}

void test_pin_value(void) {
    /* on a pin set to out, can we turn it to low and high */

    // should be low to start
    const char* msg1 = "pin is set to '0'";
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(LOW, get_value(GPIO18), strlen(LOW), msg1);

    // turn pin to "1"
    set_value(GPIO18, HIGH);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(HIGH, get_value(GPIO18), strlen(HIGH), msg1);

    // turn it off again
    set_value(GPIO18, LOW);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(LOW, get_value(GPIO18), strlen(LOW), msg1);
}

void test_catch_illegal_functions_on_unexported_pins(void) {
    /* make sure setting direction or value on unexported pin returns -1 */

    // unexport a pin

    unexport_pin(GPIO18);
    const char* msg1 = "pin was not unexported";
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg1);

    // try to set the direction
    const char* msg2 = "error was not thown on setting direction";
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, set_direction(GPIO18, IN), msg2);

    // try to set the value
    const char* msg3 = "error was not thrown on setting value";
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, set_value(GPIO18, HIGH), msg3);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, set_value(GPIO18, LOW), msg3);

    // put it back
    export_pin(GPIO18);
}

void test_setting_value_on_pin_set_to_in(void) {
    /* make sure you can't toggle a pin on or off when it is set to IN */

    // start with an in pin
    set_direction(GPIO18, IN);

    // try to set the value to high and low
    const char* msg1 = "IN pin was illegally set to HIGH";
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, set_value(GPIO18, HIGH), msg1);
    const char* msg2 = "IN pin was illegally set to HIGH";
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, set_value(GPIO18, LOW), msg2);

    // set pin back to OUT and make sure it works again
    set_direction(GPIO18, OUT);
    const char* msg3 = "OUT pin was prevented from seting to HIGH";
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, set_value(GPIO18, HIGH), msg3);
    const char* msg4 = "OUT pin was prevented from setting to LOW";
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, set_value(GPIO18, LOW), msg4);
}

int main(void) {
    UnityBegin("test/test_sysfs_gpio.c");

    RUN_TEST(test_setup);
    RUN_TEST_NO_SETUP(test_export_unexport_pin);
    RUN_TEST(test_pin_direction);
    RUN_TEST(test_pin_value);
    RUN_TEST(test_catch_illegal_functions_on_unexported_pins);
    RUN_TEST(test_setting_value_on_pin_set_to_in);
    UnityEnd();

    return EXIT_SUCCESS;
}
