/*
   sysfs_gpio.c
   control gpio pins using sysfs
 */

/* current gpio pins for single circuit */

#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIN_IN 18;
#define RAIN_OUT 23;

int create_pin(struct Pin pin) {
  /* export a pin */
  FILE* handler = fopen(pin.fexport, "r+");
  if (!handler) {
    perror("error on fopen in create_pin()");
    return EXIT_FAILURE;
  }
  fputs(pin.num, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}

int remove_pin(struct Pin pin) {
  /* unexport a pin */
  FILE* handler = fopen(pin.funexport, "r+");
  if (!handler) {
    perror("error on fopen in remove_pin()");
    return EXIT_FAILURE;
  }
  fputs(pin.num, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}
