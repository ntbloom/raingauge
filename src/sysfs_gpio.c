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

int _write_to_file(const char* msg, const char* fdesc) {
  /* write a string to a file */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    char msg[255];
    sprintf("fopen error on write: %s", fdesc);
    perror(msg);
    return EXIT_FAILURE;
  }
  fputs(msg, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}

int create_pin(struct Pin pin) {
  /* export a pin */
  return _write_to_file(pin.num, pin.fexport);
}

int remove_pin(struct Pin pin) {
  /* unexport a pin */
  return _write_to_file(pin.num, pin.funexport);
}

int set_direction(struct Pin pin, const char* direction) {
  // set direction of a pin
  // why is this causing a segfault?
  return _write_to_file(direction, pin.fdirection);
}

const char* get_direction(struct Pin pin) {
  // get direction of a pin
  return "out";
}

/*
 * BAD CODE
 *
 *
 *
 */

/*
const char* get_direction(struct Pin pin) {
  // get direction of a pin
  return _read_file(pin.fdirection);
}


char* _read_file(const char* fdesc) {
  // read contents of a file
  FILE* handler = fopen(fdesc, "r+");
  printf("fdesc=%s", fdesc);
  if (!handler) {
    char msg[255];
    sprintf("fopen error on read: %s", fdesc);
    perror(msg);
  }
  char buf[255];
  fscanf(handler, buf);
  fclose(handler);
  if (strcmp(buf, "in") == 0) {
    return "in";
  } else if (strcmp(buf, "out") == 0) {
    return "out";
  }
}
*/
