#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

int _write_num_to_file(int pin, const char* fdesc);
int create_pin(int pin);
int remove_pin(int pin);
int set_direction(int pin, const char* dir);
const char* get_direction(int pin);
int turn_on(int pin);
int value(int pin);

#endif
