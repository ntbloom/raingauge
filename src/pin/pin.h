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
    // file descriptors
    const char* snum;         // pin number as string, ie: "18"
    const char* fdesc;        // general file for the pin, ie: "/sys/class/gpio/gpio18"
    const char* fdirec;       // file for direction, ie : ".../gpio18/direction"
    const char* fvalue;       // file for value, ie: ".../gpio18/value"
    const char* fedge;        // file for edge, ie: ".../gpio18/edge"
    const char* factive_low;  // file for active_low, ie : ".../gpio18/active_low"

    // other data points
    size_t num;       // numeric representation of pin number, ie 18
    bool direc_out;   // pin direction: true = "out", false = "in"
    bool value_hi;    //  pin value: true = "high", false = "low"
    int edge;         // none = 0; rising = 1; falling = 2
    bool active_low;  // 0 = false, 1 = true
};
Pin* construct_pin(size_t);
int deconstruct_pin(Pin*);

#endif
