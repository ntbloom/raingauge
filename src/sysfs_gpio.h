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

/* Pin struct representing a GPIO Pin over sysfs using the file descriptors located at
 * on a Linux machine at `/sys/class/gpio/`. Create and destroy Pin objects using the
 * `construct_pin()` and `deconstruct_pin()` methods.
 */

typedef struct Pin Pin;
struct Pin {
    const char* num;    // pin number; corresponds to `pinout` command on raspberry pi
    const char* fdesc;  // sysfs file for the pin, ie: /sys/class/gpio/gpio18
    const char* fdirection;  // sysfs file for direction, ie : .../gpio18/direction
    const char* fvalue;      // sysfs file for value, ie: .../gpio18/value
};
Pin* construct_pin(int);
int deconstruct_pin(Pin*);

/* Look up information about a Pin directly from the file descriptor */
int set_direction(struct Pin, const char*);
const char* get_direction(Pin);
int set_value(Pin, const char*);
const char* get_value(Pin);

/* helper functions */
int export_pin(Pin);
int unexport_pin(Pin);
int write_to_file(const char*, const char*);
char* read_file(const char*);
int file_exists(const char*, int, int);

#endif
