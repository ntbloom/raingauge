#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/pin.h"
#include "../src/sysfs.h"
#include "vendor/unity.h"

const char* msg = "18";
const char* fdesc = "/sys/class/gpio/gpio18";

void setUp(void) {
    // export a pin where it previously did not exist
    write_to_file(msg, EXPORT);
}
void tearDown(void) {
    // unexport pin at the end of the tests
    write_to_file(msg, UNEXPORT);
}

void test_file_exists_with_timeout(void) {
    /* make sure `gpio/gpio18` is created and exists */
    const char* err = "pin was not exported";
    TEST_ASSERT_EQUAL_INT_MESSAGE(EXIT_SUCCESS, file_exists(fdesc, F_OK, 1), err);
}

void test_file_exists_without_timeout(void) {
    /* make sure `gpio/gpio18` is created and exists */
    const char* err = "pin was not exported";
    TEST_ASSERT_EQUAL_INT_MESSAGE(EXIT_SUCCESS, file_exists(fdesc, F_OK, 0), err);
}

void test_read_and_write_file(void) {
    /* read and write a direction file to IN and OUT */
    const char* direction = "/sys/class/gpio/gpio18/direction";

    // set to out
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, write_to_file(OUT, direction));
    TEST_ASSERT_EQUAL_INT(0, strncmp(OUT, read_file(direction), strlen(OUT)));

    // set to in
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, write_to_file(IN, direction));
    TEST_ASSERT_EQUAL_INT(0, strncmp(IN, read_file(direction), strlen(IN)));
}

int main(void) {
    UnityBegin("test/test_sysfs.c");

    RUN_TEST(test_file_exists_with_timeout);
    RUN_TEST(test_file_exists_without_timeout);
    RUN_TEST(test_read_and_write_file);
    UnityEnd();

    return EXIT_SUCCESS;
}
