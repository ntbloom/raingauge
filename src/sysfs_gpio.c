/*
   sysfs_gpio.c
   control gpio pins using sysfs
 */

/* current gpio pins for single circuit */

#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* err = malloc(255);  // TODO: can i delete?
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

int set_direction(struct Pin pin, const char* direction) {
  /* set the direction of the pin */
  return _write_to_file(direction, pin.direction);
}

const char* get_direction(struct Pin pin) {
  /* get direction of the pin */
  char* err = malloc(255);
  char* direction = malloc(5);
  FILE* handler = fopen(pin.direction, "r");
  if (!handler) {
    sprintf(err, "fopen error on %s\n", pin.direction);
    perror(err);
    free(err);
    free(direction);
    return "";
  }
  if (fgets(direction, 4, handler) == NULL) {
    sprintf(err, "fgets error on %s\n", pin.direction);
    perror(err);
    free(err);
    free(direction);
    fclose(handler);
    return "";
  }
  if (strcmp(direction, IN) == 0) {
    free(err);
    free(direction);
    fclose(handler);
    return IN;
  } else if (strcmp(direction, OUT) == 0) {
    free(err);
    free(direction);
    fclose(handler);
    return OUT;
  }
  sprintf(err, "direction is neither in nor out");
  perror(err);
  free(err);
  free(direction);
  fclose(handler);
  return "";
}
