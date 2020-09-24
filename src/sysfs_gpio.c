/*
   sysfs_gpio.c
   control gpio pins using sysfs
 */

#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int _write_to_file(const char* msg, const char* fdesc) {
  /* write a string to a file */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d:\n\tfopen error on write: %s\n", __LINE__,
            fdesc);
    perror(err);
    free(err);
    return EXIT_FAILURE;
  }
  if (fputs(msg, handler) == -1) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d: \n\tfputs error on msg=%s\n", __LINE__, msg);
    perror(err);
    fclose(handler);
    free(err);
    return EXIT_FAILURE;
  }
  if (fclose(handler) == -1) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d:\n\tfclose error on %s\n", __LINE__, fdesc);
    perror(err);
    free(err);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

char* _read_file(const char* fdesc) {
  /* get contents of a file */
  while (access(fdesc, W_OK) != 0) {
    continue;
  }
  char* contents = malloc(5);
  FILE* handler = fopen(fdesc, "r");
  if (!handler) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d:\n\tfopen error on %s\n", __LINE__, fdesc);
    perror(err);
    free(err);
    return "";
  }
  if (fgets(contents, sizeof(contents), handler) == NULL) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d:\n\tfgets error on %s\n", __LINE__, fdesc);
    perror(err);
    free(err);
    sprintf(contents, "");
  }
  return contents;
}

int create_pin(struct Pin pin) {
  /* export a pin */
  _write_to_file(pin.num, EXPORT);

  clock_t start_t, end_t;
  start_t = clock();
  end_t = clock();

  while (access(pin.fdesc, F_OK) != 0 &&
         ((end_t - start_t) / CLOCKS_PER_SEC <= TIMEOUT)) {
    end_t = clock();
  }
  if (access(pin.fdesc, F_OK) != 0) {
    char* err = malloc(255);
    sprintf(err, "ERROR LINE %d:\n\terror turning on pin at %s\n", __LINE__,
            pin.fdesc);
    perror(err);
    free(err);
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}

int remove_pin(struct Pin pin) {
  /* unexport a pin */
  return _write_to_file(pin.num, UNEXPORT);
}

int set_direction(struct Pin pin, const char* direction) {
  /* set the direction of the pin */
  while (access(pin.direction, W_OK) != 0) {
    continue;
  }
  return _write_to_file(direction, pin.direction);
}

const char* get_direction(struct Pin pin) {
  //  get the direction of a pin
  char* direction = _read_file(pin.direction);
  if (strcmp(direction, IN) == 0) {
    free(direction);
    return IN;
  } else if (strcmp(direction, OUT) == 0) {
    free(direction);
    return OUT;
  }
  free(direction);
  return "";
}
