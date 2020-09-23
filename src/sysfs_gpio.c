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
#define HIGH "1"
#define LOW "0"

int _write_to_file(const char* msg, const char* fdesc) {
  /* write a string to a file */
  char* err = malloc(255);
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    sprintf(err, "fopen error on write: %s\n", fdesc);
    perror(err);
    free(err);
    return EXIT_FAILURE;
  }
  if (fputs(msg, handler) == -1) {
    sprintf(err, "fputs error on msg=%s", msg);
    perror(err);
    fclose(handler);
    free(err);
    return EXIT_FAILURE;
  }
  if (fclose(handler) == -1) {
    char* err = malloc(255);
    sprintf(err, "fclose error on %s", fdesc);
    perror(err);
    free(err);
    return EXIT_FAILURE;
  }
  free(err);
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

