/*
   test_sysfs_gpio.c
 */

#include <stdlib.h>
#include <unistd.h>
#include "../src/sysfs_gpio.h"
#include "vendor/unity.h"

int PIN = 18;
const char* FDESC = "/sys/class/gpio/gpio18/";

void setUp(void) {
  /* create a pin where it previously did not exist */
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, create_pin(PIN), "problem in create_pin()");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(FDESC, F_OK), "gpio18 not created");
}
void tearDown(void) {
  /* unexport pin at the end of the tests */
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, remove_pin(PIN), "problem in remove_pin()");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(FDESC, F_OK),
                                "gpio18 was not unexported");
}

void test_giving_direction(void) {
  /* a pin gets set to in and out*/

  // given a pin
  int pin = 18;
  create_pin(pin);

  // set it to out
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, set_direction(pin, "out"),
                                "problem with direction('out')");
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("out", get_direction(pin), 4,
                                       "gpio18 is not set to `out`");

  // set it to in
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, set_direction(pin, "in"),
                                "problem with direction('in')");
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("in", get_direction(pin), 3,
                                       "gpio18 is not set to `in`");
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST(test_giving_direction);

  UnityEnd();

  return EXIT_SUCCESS;
}
