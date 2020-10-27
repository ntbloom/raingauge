#ifndef PIN_H
#define PIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include "constants.h"
#include "sysfs.h"

/* Pin struct representing a GPIO Pin over sysfs using the file descriptors located at
 * on a Linux machine at `/sys/class/gpio/`. Create and destroy Pin objects using the
 * `construct_pin()` and `deconstruct_pin()` methods.
 */
typedef struct Pin Pin;
struct Pin {
    // file descriptors
    const char* num;         // pin number as string, ie: "18"
    const char* desc;        // general file for the pin, ie: "/sys/class/gpio/gpio18"
    const char* direc;       // file for direction, ie : ".../gpio18/direction"
    const char* value;       // file for value, ie: ".../gpio18/value"
    const char* edge;        // file for edge, ie: ".../gpio18/edge"
    const char* active_low;  // file for active_low, ie : ".../gpio18/active_low"
};
Pin* construct_pin(size_t);
int deconstruct_pin(Pin*);

/* Methods to be used on a pin. Since they rely on the filesystem and the existence of the
 * basic file descriptor, these can only be called on a pin that has already been
 * exported. Additional criteria like pin direction or value may also be checked as
 * needed.
 */
int poll_pin(Pin*);

#endif
