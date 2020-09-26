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
    const char* num;    // pin number; corresponds to `pinout` command on raspberry pi
    const char* fdesc;  // sysfs file for the pin, ie: /sys/class/gpio/gpio18
    const char* fdirection;  // sysfs file for direction, ie : .../gpio18/direction
    const char* fvalue;      // sysfs file for value, ie: .../gpio18/value
};

/* Grant and revoke GPIO Pin access using the `export` and `unexport` terminology from
 * sysfs. By default all new pins are set to "in" after being exported. The value of the
 * pin depends on what is coming into the Pin.
 *
 * Setting/reading direction or value on an unexported Pin will fail.
 */
int export_pin(Pin);
int unexport_pin(Pin);

/* Look up information about a Pin directly from the file descriptor */
int set_direction(struct Pin, const char*);
const char* get_direction(Pin);
int set_value(Pin, const char*);
const char* get_value(Pin);

/* helper functions */
int write_to_file(const char*, const char*);
char* read_file(const char*);
int file_exists(const char*, int, int);

#endif
