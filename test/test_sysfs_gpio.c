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
  TEST_ASSERT_EQUAL_INT(0, create_pin(PIN));
  TEST_ASSERT_EQUAL_INT(0, access(FDESC, F_OK));
}
void tearDown(void) {
  /* unexport pin at the end of the tests */
  TEST_ASSERT_EQUAL_INT(0, remove_pin(PIN));
  TEST_ASSERT_EQUAL_INT(-1, access(FDESC, F_OK));
}

void test_giving_direction(void) {
  /* a pin gets set to in and out*/

  // given a pin
  int pin = 18;
  create_pin(pin);

  // set it to out
  TEST_ASSERT_EQUAL_INT(0, set_direction(pin, "out"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("out", get_direction(pin), 4);

  // set it to in
  TEST_ASSERT_EQUAL_INT(0, set_direction(pin, "in"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("in", get_direction(pin), 3);
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST(test_giving_direction);

  UnityEnd();

  return EXIT_SUCCESS;
}
