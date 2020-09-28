#include "pin.h"

/* create a new Pin */
Pin* construct_pin(size_t number) {
    if (number > MAX_PIN || number <= 0) {
        // TODO: prevent illegal pins, like gnd
        return NULL;
    };

    // create the pin
    Pin* pin = malloc(sizeof(Pin));
    size_t base_n = strlen(SYSFS) + 1;
    size_t snum_n = strlen("GPIOXX/");
    size_t fdesc_n = base_n + snum_n;
    size_t fdirec_n = fdesc_n + strlen("direction");
    size_t fvalue_n = fdesc_n + strlen("value");

    char* snum = malloc(snum_n);
    sprintf(snum, "%d", number);
    pin->snum = snum;

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
    pin->value_on = false;

    // export the pin to make it available in the filesystem
    if (write_to_file(snum, EXPORT) != EXIT_SUCCESS) {
        perror("failure to export pin");
        fprintf(stderr, "\tsnum=%s\n\tEXPORT=%s\n", snum, EXPORT);
        return NULL;
    }

    // TODO: read its value
    return pin;
}

/* deconstruct a Pin */
int deconstruct_pin(Pin* pin_ptr) {
    if (write_to_file(pin_ptr->snum, UNEXPORT) != EXIT_SUCCESS) {
        perror("failure to unexport pin");
        return EXIT_FAILURE;
    }

    free((void*)pin_ptr->snum);
    free((void*)pin_ptr->fdesc);
    free((void*)pin_ptr->fdirec);
    free((void*)pin_ptr->fvalue);
    free(pin_ptr);
    return EXIT_SUCCESS;
}
