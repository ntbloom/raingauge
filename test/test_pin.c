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

void test_setup(void) {
    /* if this test fails, the `setUp()` function was misconfigured */
    TEST_ASSERT_EQUAL_INT(1, 1);
    TEST_ASSERT_EQUAL(false, 0);
}

void test_construct_pin(void) {
    /* basic test of the constructor, run test with valgrind to confirm */
    size_t num = 18;
    Pin* pin = construct_pin(num);

    const char* fdesc = "/sys/class/gpio/gpio18";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fdesc, pin->fdesc, "bad fdesc");

    const char* fdirec = "/sys/class/gpio/gpio18/direction";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fdirec, pin->fdirec, "bad fdirect");

    const char* fvalue = "/sys/class/gpio/gpio18/value";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(fvalue, pin->fvalue, "bad fvalue");

    TEST_ASSERT_EQUAL_INT_MESSAGE(false, pin->direc_out, "bad direc_on");
    TEST_ASSERT_EQUAL_INT_MESSAGE(false, pin->value_on, "bad value_in");

    deconstruct_pin(pin);
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_setup);
    RUN_TEST(test_construct_pin);

    UnityEnd();

    return EXIT_SUCCESS;
}
