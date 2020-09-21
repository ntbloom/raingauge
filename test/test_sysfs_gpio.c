/*
   test_sysfs_gpio.c
 */

#include <stdlib.h>
#include <unistd.h>
#include "../src/sysfs_gpio.h"
#include "vendor/unity.h"

#define RUN_TEST_NO_SETUP(testfunc) \
  UNITY_NEW_TEST(#testfunc)         \
  if (TEST_PROTECT()) {             \
    testfunc();                     \
  }                                 \
  UnityConcludeTest();

int PIN = 18;
const char* FDESC = "/sys/class/gpio/gpio18/";

void setUp(void) {
  /* export a pin where it previously did not exist */
  create_pin(PIN);
}
void tearDown(void) {
  /* unexport pin at the end of the tests */
  remove_pin(PIN);
}

void test_export_unexport_pin(void) {
  /* can we turn on and turn off a pin */
  // given a pin
  const char* msg1 = "pin already exists";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(FDESC, F_OK), msg1);

  // turn it on
  create_pin(PIN);
  const char* msg2 = "pin not created";
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(FDESC, F_OK), msg2);

  // turn it back off again
  remove_pin(PIN);
  const char* msg3 = "pin was not unexported";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(FDESC, F_OK), msg3);
}

void test_giving_direction(void) {
  /* a pin gets set to in and out*/

  // set it to out and verify
  set_direction(PIN, "out");
  const char* msg1 = "pin not set to `out`";
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("out", get_direction(PIN), 4, msg1);

  // set it to in and verify

  set_direction(PIN, "in");
  const char* msg2 = "pin not set to `in`";
  TEST_ASSERT_EQUAL_CHAR_ARRAY("in", get_direction(PIN), msg2);
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST_NO_SETUP(test_export_unexport_pin);
  RUN_TEST(test_giving_direction);

  UnityEnd();

  return EXIT_SUCCESS;
}
