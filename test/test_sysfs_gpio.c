/*
   test_sysfs_gpio.c
 */

#include <stdlib.h>
#include <unistd.h>
#include "../src/sysfs_gpio.h"
#include "vendor/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_export_unexport_pin(void) {
  /* can we turn on and turn off a pin */
  // given a pin
  int pin = 18;
  const char* fdescr = "/sys/class/gpio/gpio18/";
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(fdescr, F_OK),
                                "gpio18 already exists");

  // turn it on
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, create_pin(pin), "problem in create_pin()");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, access(fdescr, F_OK), "gpio18 not created");

  // turn it back off again
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, remove_pin(pin), "problem in remove_pin()");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, access(fdescr, F_OK),
                                "gpio18 was not unexported");
}

int main(void) {
  UnityBegin("test/test_sysfs_gpio.c");

  RUN_TEST(test_export_unexport_pin);

  UnityEnd();

  return EXIT_SUCCESS;
}
