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

struct Pin const GPIO18 = {.num = "18",
                           .fdesc = "/sys/class/gpio/gpio18",
                           .direction = "/sys/class/gpio/gpio18/direction",
                           .value = "/sys/class/gpio/gpio18/value"};

void setUp(void) {
  // export a pin where it previously did not exist
  create_pin(GPIO18);
}
void tearDown(void) {
  // unexport pin at the end of the tests
  remove_pin(GPIO18);
}

void test_export_unexport_pin(void) {
  // can we turn on and turn off a pin
  // given a pin
  const char* msg1 = "pin already exists";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg1);

  // turn it on
  create_pin(GPIO18);
  const char* msg2 = "pin not created";
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(GPIO18.fdesc, F_OK), msg2);

  // turn it back off again
  remove_pin(GPIO18);
  const char* msg3 = "pin was not unexported";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fdesc, F_OK), msg3);
}

void test_pin_direction(void) {
  // set the direction out and in and out
  set_direction(GPIO18, IN);
  const char* msg1 = "pin is set to 'in'";
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("out", get_direction(GPIO18), 4, msg1);

  set_direction(GPIO18, IN);
  const char* msg2 = "pin is set to 'out'";
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("in", get_direction(GPIO18), 3, msg2);

  set_direction(GPIO18, IN);
  TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE("out", get_direction(GPIO18), 4, msg1);
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST_NO_SETUP(test_export_unexport_pin);
  RUN_TEST(test_pin_direction);

  UnityEnd();

  return EXIT_SUCCESS;
}
