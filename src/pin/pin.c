#include "pin.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../common/constants.h"
#include "../sysfs/sysfs.h"

/* create a new Pin */
Pin* construct_pin(size_t number) {
    if (number > MAX_PIN) {
        return NULL;
    };

    int base = strlen(SYSFS) + 9;  // allows for 3-digit pins
    char* snum = malloc(4);
    sprintf(snum, "%d", number);

    char* fdesc = malloc(base);
    sprintf(fdesc, SYSFS "%d", number);

    char* fdirection = malloc(sizeof(base) + 9);
    sprintf(fdirection, SYSFS "%d/direction", number);

    char* fvalue = malloc(sizeof(base) + 5);
    sprintf(fvalue, SYSFS "%d/value", number);

    // create a pin, find out its value
    if (write_to_file(snum, EXPORT) != EXIT_SUCCESS) {
        return NULL;
    };

    Pin pin = {snum = snum, fdesc, fdirection, fvalue, number, 0, 0};

    Pin* p = NULL;
    return p;
}

/* deconstruct a Pin */
int deconstruct_pin(Pin* pin) {
    // do some stuff
    return EXIT_SUCCESS;
}
/*  get the direction of a pin */
const char* get_direction(Pin pin) {
    char* direction = read_file(pin.fdirection);
    if (strncmp(direction, IN, strlen(IN)) == 0) {
        free(direction);
        return IN;
    } else if (strncmp(direction, OUT, strlen(OUT)) == 0) {
        free(direction);
        return OUT;
    }
    free(direction);
    return "";
}
