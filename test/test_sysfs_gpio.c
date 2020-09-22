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
                           .fname = "/sys/class/gpio/gpio18",
                           .fexport = "/sys/class/gpio/export",
                           .funexport = "/sys/class/gpio/unexport",
                           .fdirection = "/sys/class/gpio/gpio18/direction",
                           .fvalue = "/sys/class/gpio/gpio18/value"};

void setUp(void) {
  /* export a pin where it previously did not exist */
  create_pin(GPIO18);
}
void tearDown(void) {
  /* unexport pin at the end of the tests */
  remove_pin(GPIO18);
}

void test_export_unexport_pin(void) {
  /* can we turn on and turn off a pin */
  // given a pin
  const char* msg1 = "pin already exists";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fname, F_OK), msg1);

  // turn it on
  create_pin(GPIO18);
  const char* msg2 = "pin not created";
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(GPIO18.fname, F_OK), msg2);

  // turn it back off again
  remove_pin(GPIO18);
  const char* msg3 = "pin was not unexported";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(GPIO18.fname, F_OK), msg3);
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST_NO_SETUP(test_export_unexport_pin);

  UnityEnd();

  return EXIT_SUCCESS;
}
