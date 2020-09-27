#ifndef PIN_H
#define PIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../common/constants.h"
#include "../sysfs/sysfs.h"

/* Pin struct representing a GPIO Pin over sysfs using the file descriptors located at
 * on a Linux machine at `/sys/class/gpio/`. Create and destroy Pin objects using the
 * `construct_pin()` and `deconstruct_pin()` methods.
 */
typedef struct Pin Pin;
struct Pin {
    const char* snum;    // pin number as string; see `pinout` command on raspberry pi
    const char* fdesc;   // sysfs file for the pin, ie: /sys/class/gpio/gpio18
    const char* fdirec;  // sysfs file for direction, ie : .../gpio18/direction
    const char* fvalue;  // sysfs file for value, ie: .../gpio18/value

    size_t num;      // gpio number as a digit
    bool direc_out;  // on true, pin is set to "out", on false set to "in"
    bool value_on;   //  true is "high", false is "low"
};
Pin* construct_pin(size_t);
int deconstruct_pin(Pin*);

#endif
