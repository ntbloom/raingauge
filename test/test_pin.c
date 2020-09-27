#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/pin/pin.h"
#include "vendor/unity.h"

// TODO: use these values to verify tests on pin 18
/*
int direction = 0;
int value = 0;
*/

void setUp(void) {
    // export a pin where it previously did not exist
}
void tearDown(void) {
    // unexport pin at the end of the tests
}

/* if this test fails, the `setUp()` function was misconfigured */
void test_setup(void) {
    TEST_ASSERT_EQUAL_INT(1, 1);
    TEST_ASSERT_EQUAL(false, 0);
}

/* basic test of the constructor, run `make memtest` to confirm memory safety*/
void test_construct_pin(void) {
    size_t num = 18;
    Pin* pin_ptr = construct_pin(num);
    TEST_ASSERT_NOT_NULL(pin_ptr);

    const char* fdesc = "/sys/class/gpio/gpio18";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fdesc, pin_ptr->fdesc, "bad fdesc");

    const char* fdirec = "/sys/class/gpio/gpio18/direction";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fdirec, pin_ptr->fdirec, "bad fdirect");

    const char* fvalue = "/sys/class/gpio/gpio18/value";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fvalue, pin_ptr->fvalue, "bad fvalue");

    TEST_ASSERT_EQUAL_INT_MESSAGE(false, pin_ptr->direc_out, "bad direc_on");
    TEST_ASSERT_EQUAL_INT_MESSAGE(false, pin_ptr->value_on, "bad value_in");

    deconstruct_pin(pin_ptr);
}

/* make sure constructor turns on pin and deconstructor turns it off */
void test_automatic_export_unexport(void) {
    size_t num = 18;
    Pin* pin_ptr = construct_pin(num);
    TEST_ASSERT_NOT_NULL(pin_ptr);

    TEST_ASSERT_MESSAGE(access(pin_ptr->fdesc, F_OK) == 0, "pin not exported");

    deconstruct_pin(pin_ptr);
    TEST_ASSERT_MESSAGE(access(pin_ptr->fdesc, F_OK) != 0, "pin not unexported");
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_setup);
    RUN_TEST(test_construct_pin);
    RUN_TEST(test_automatic_export_unexport);

    UnityEnd();

    return EXIT_SUCCESS;
}
