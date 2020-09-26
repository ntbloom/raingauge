#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

#define OUT "out"
#define IN "in"
#define SYSFS "/sys/class/gpio/"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"
#define HIGH "1"
#define LOW "0"
#define TIMEOUT 1

typedef struct Pin Pin;
struct Pin {
    /* Representing a gpio pin */
    const char* num;         // pin number on raspberry pi 3
    const char* fdesc;       // sysfs file for the pin, ie: /sys/class/gpio/gpio18
    const char* fdirection;  // sysfs file for direction, ie : .../gpio18/direction
    const char* fvalue;      // sysfs file for value, ie: .../gpio18/value
};

int export_pin(Pin);
int unexport_pin(Pin);

int _write_to_file(const char*, const char*);
char* _read_file(const char*);

const char* get_direction(Pin);
int set_direction(struct Pin, const char*);
int set_value(Pin, const char*);
const char* get_value(Pin);
int file_exists(const char*, int, int);

#endif
