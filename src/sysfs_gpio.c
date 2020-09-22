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
  return _write_to_file(pin.num, pin.fexport);
}

int remove_pin(struct Pin pin) {
  /* unexport a pin */
  return _write_to_file(pin.num, pin.funexport);
}

const char* get_direction(struct Pin pin) {
  /* get direction of a pin */
  return "";
}

int set_direction(struct Pin pin, const char* dir) {
  /* set direction of a pin */
  return EXIT_SUCCESS;
}

int _write_to_file(const char* msg, const char* fdesc) {
  /* write a string to a file */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    perror("error on fopen");
    return EXIT_FAILURE;
  }
  fputs(msg, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}
