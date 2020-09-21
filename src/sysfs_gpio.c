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

int create_pin(int pin) {
  /* export a pin */
  return _write_pin_num_to_file(pin, "/sys/class/gpio/export");
}

int remove_pin(int pin) {
  /* unexport a pin */
  return _write_pin_num_to_file(pin, "/sys/class/gpio/unexport");
}

int _write_pin_num_to_file(int pin, const char* fdesc) {
  /* write number to file descriptor */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    perror("error on fopen");
    return EXIT_FAILURE;
  }
  char pin_str[10];
  sprintf(pin_str, "%d\n", pin);
  fputs(pin_str, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}

int _write_string_to_file(const char* msg, const char* fdesc) {
  /* write a message to a file descriptor */
  FILE* handler = fopen(fdesc, "r+");
  if (!handler) {
    perror("error on fopen");
    return EXIT_FAILURE;
  }
  fputs(msg, handler);
  fclose(handler);
  return EXIT_SUCCESS;
}

char* _get_full_gpio_name(int pin) {
  /* get full sysfs path for a given pin */
  char buf[50];
  sprintf(buf, "/sys/class/gpio/gpio%d", pin);
  char* path = malloc(50);
  strcpy(path, buf);
  return path;
}

int set_direction(int pin, const char* dir) {
  /* specify the direction of a pin */
  char* path = _get_full_gpio_name(pin);
  _write_string_to_file(dir, path);
  free(path);

  return EXIT_SUCCESS;
}

const char* get_direction(int pin) {
  /* get the direction of a pin */
  return "";
}

int set_value(int pin) {
  /* turn on a pin */
  return EXIT_SUCCESS;
}

int get_value(int pin) {
  /* what is the value of the pin? */
  return EXIT_SUCCESS;
}
