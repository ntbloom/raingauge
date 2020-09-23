/*
   sysfs_gpio.c
   control gpio pins using sysfs
 */

/* current gpio pins for single circuit */

#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT "out";
#define IN "in";
#define SYSFS "/sys/class/gpio/"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"

int _write_to_file(const char* msg, const char* fdesc) {
  /* write a string to a file */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    char err[255];
    sprintf(err, "fopen error on write: %s\n", fdesc);
    perror(err);
    return EXIT_FAILURE;
  }
  if (fputs(msg, handler) == -1) {
    char err[255];
    sprintf(err, "fputs error on msg=%s", msg);
    perror(err);
    fclose(handler);
    return EXIT_FAILURE;
  }
  if (fclose(handler) == -1) {
    char err[255];
    sprintf(err, "fclose error on %s", fdesc);
    perror(err);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int create_pin(struct Pin pin) {
  /* export a pin */
  return _write_to_file(pin.num, EXPORT);
}

int remove_pin(struct Pin pin) {
  /* unexport a pin */
  return _write_to_file(pin.num, UNEXPORT);
}

/*
 * BAD CODE
 *
 *
 *
 */

/*

int set_direction(struct Pin pin, const char* direction) {
  // set direction of a pin
  // why is this causing a segfault?
  return _write_to_file(direction, pin.direction);
}

const char* get_direction(struct Pin pin) {
  // get direction of a pin
  return "out";
}

struct Pin make_pin(int i) {
  // make a Pin struct from just a number
  char* num = malloc(8);
  sprintf(num, "%d", i);
  // TODO: finish
}

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
