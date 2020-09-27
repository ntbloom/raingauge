#include "pin.h"

/* create a new Pin */
Pin* construct_pin(size_t number) {
    if (number > MAX_PIN || number <= 0) {
        // TODO: prevent illegal pins, like gnd
        return NULL;
    };

    Pin* pin = malloc(sizeof(Pin));
    // string lengths for malloc
    size_t base_n = strlen(SYSFS + 1);
    size_t snum_n = strlen("GPIOXX/");
    size_t fdesc_n = base_n + snum_n;
    size_t fdirec_n = fdesc_n + strlen("direction");
    size_t fvalue_n = fdesc_n + strlen("value");

    char* snum = malloc(snum_n);
    sprintf(snum, "GPIO%d", number);
    pin->snum = NULL;

    char* fdesc = malloc(fdesc_n);
    sprintf(fdesc, SYSFS "gpio%d", number);
    pin->fdesc = fdesc;

    char* fdirec = malloc(fdirec_n);
    sprintf(fdirec, SYSFS "gpio%d/direction", number);
    pin->fdirec = fdirec;

    char* fvalue = malloc(fvalue_n);
    sprintf(fvalue, SYSFS "gpio%d/value", number);
    pin->fvalue = fvalue;

    pin->num = number;
    pin->direc_out = false;
    pin->value_on = 0;

    return pin;
}

/* deconstruct a Pin */
int deconstruct_pin(Pin** pin) {
    free(pin);
    *pin = NULL;
    return EXIT_SUCCESS;
}
