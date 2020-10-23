#include <fcntl.h>
#include <poll.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/constants.h"
#include "../src/pin.h"
#include "../src/sysfs.h"
#include "vendor/unity.h"

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

    const char* desc = "/sys/class/gpio/gpio18";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(desc, pin_ptr->desc, "bad desc");

    const char* direc = "/sys/class/gpio/gpio18/direction";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(direc, pin_ptr->direc, "bad direct");

    const char* value = "/sys/class/gpio/gpio18/value";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(value, pin_ptr->value, "bad value");

    const char* edge = "/sys/class/gpio/gpio18/edge";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(edge, pin_ptr->edge, "bad edge");

    const char* active_low = "/sys/class/gpio/gpio18/active_low";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(active_low, pin_ptr->active_low, "bad active_low");

    deconstruct_pin(pin_ptr);
}

/* make sure constructor turns on pin and deconstructor turns it off */
void test_automatic_export_unexport(void) {
    size_t num = 18;
    Pin* pin_ptr = construct_pin(num);
    TEST_ASSERT_NOT_NULL(pin_ptr);

    const char* gpio18 = "/sys/class/gpio/gpio18";
    TEST_ASSERT_MESSAGE(file_exists(gpio18, F_OK, 1) == 0, "pin not exported");

    deconstruct_pin(pin_ptr);
    TEST_ASSERT_MESSAGE(file_exists(gpio18, F_OK, 1) != 0, "pin not unexported");
}

/* check that the constructor/desctructor works with all legal pins, 0 through 26
 * inclusive except GPIO4.
 */
void test_all_legal_pins(void) {
    for (int i = 0; i <= MAX_PIN; i++) {
        Pin* pin_ptr = construct_pin(i);

        /* pin 4 not legal on pi3b */
        if (i == 4) {
            TEST_ASSERT_NULL(pin_ptr);
            continue;
        }

        char* err = malloc(50);
        sprintf(err, "problem exporting pin %d", i);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->desc, W_OK, 1) != EXIT_FAILURE, err);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->value, W_OK, 1) != EXIT_FAILURE, err);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->direc, W_OK, 1) != EXIT_FAILURE, err);
        free(err);
        deconstruct_pin(pin_ptr);
    }
}

/* test the polling function */
void test_poll(void) {
    /* create a pin, set edge to "rising" */
    Pin* pin_ptr = construct_pin(18);
    write_to_file("rising", pin_ptr->edge);

    poll_pin(pin_ptr); /* TODO: do something with this! */

    deconstruct_pin(pin_ptr);
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_setup);
    RUN_TEST(test_construct_pin);
    RUN_TEST(test_automatic_export_unexport);
    RUN_TEST(test_all_legal_pins);
    RUN_TEST(test_poll);

    UnityEnd();

    return EXIT_SUCCESS;
}
