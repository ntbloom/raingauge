#ifndef PIN_H
#define PIN_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include "constants.h"
#include "poll.h"
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

/* Create a new Pin struct corresponding to a legal GPIO pin. Provide an integer between
 * MIN_PIN and MAX_PIN and the constructor provides the rest, including exporting that
 * number to /sys/class/gpio/export.  By default all pins are set to IN, so we read the
 * value in case it's already receiving data.
 */
Pin* construct_pin(size_t);

/* Remove a pin when you're done with it. The deconstructor first removes the pin from
 * the filesystem using /sysfs/class/gpio/unexport, then frees all of the memory.
 */
int deconstruct_pin(Pin*);

/* prep a pin to be polled high */
int await_high(Pin*);

/* poll a pin high until thread is called */
int poll_value(Pin*, int (*)(void));

#endif
