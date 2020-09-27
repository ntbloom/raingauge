#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/pin/pin.h"
#include "vendor/unity.h"

void setUp(void) {
    // export a pin where it previously did not exist
}
void tearDown(void) {
    // unexport pin at the end of the tests
}

void test_setup(void) {
    /* if this test fails, the `setUp()` function was misconfigured */
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_setup);

    UnityEnd();

    return EXIT_SUCCESS;
}
