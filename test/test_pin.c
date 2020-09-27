#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/pin/pin.h"
#include "vendor/unity.h"

// TODO: use these values to verify tests on pin 18
/*
const char* fdesc = "/sys/class/gpio/gpio18";
const char* fdirection = "/sys/class/gpio/gpio18/direction";
const char* fvalue = "/sys/class/gpio/gpio18/value";
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

void test_construct_pin_memsafety(void) {
    /* basic test of the constructor, run test with valgrind to confirm */
    size_t num = 18;
    Pin* p = construct_pin(num);
    deconstruct_pin(&p);
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_setup);
    RUN_TEST(test_construct_pin_memsafety);

    UnityEnd();

    return EXIT_SUCCESS;
}
