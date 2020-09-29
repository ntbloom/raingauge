#include "pin.h"

/* Create a new Pin struct corresponding to a legal GPIO pin. Provide an integer between
 * MIN_PIN and MAX_PIN and the constructor provides the rest, including exporting that
 * number to /sys/class/gpio/export.  By default all pins are set to IN, so we read the
 * value in case it's already receiving data.
 */
Pin* construct_pin(size_t number) {
    // don't allow  illegal
    if (number > MAX_PIN || number == 4) {
        return NULL;
    };

    // create the pin, set everything but the value
    Pin* pin = malloc(sizeof(Pin));
    size_t base_n = strlen(SYSFS) + 1;
    size_t snum_n;
    if (number < 10) {
        snum_n = strlen("GPIOX/");
    } else {
        snum_n = strlen("GPIOXX/");
    }
    size_t fdesc_n = base_n + snum_n;
    size_t fdirec_n = fdesc_n + strlen("direction");
    size_t fvalue_n = fdesc_n + strlen("value");
    size_t fedge_n = fdesc_n + strlen("edge");
    size_t factive_n = fdesc_n + strlen("active_low");

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

    char* fedge = malloc(fedge_n);
    sprintf(fedge, SYSFS "gpio%d/edge", number);
    pin->fedge = fedge;

    char* factive_low = malloc(factive_n);
    sprintf(factive_low, SYSFS "gpio%d/active_low", number);
    pin->factive_low = factive_low;

    pin->num = number;
    pin->direc_out = false;
    pin->edge = 0;
    pin->active_low = false;

    // export the pin, block until "value" is ready in the filesystem
    if (write_to_file(snum, EXPORT) != EXIT_SUCCESS) {
        perror("failure to export pin");
        fprintf(stderr, "\tsnum=%s\n\tEXPORT=%s\n", snum, EXPORT);
        return NULL;
    }
    if (file_exists(fvalue, W_OK, 1) != EXIT_SUCCESS) {
        perror("pin was not exported, no value exists");
        fprintf(stderr, "\tgpio%d\n", number);
        return NULL;
    }

    // set the value now that we can look it up
    char* value = read_file(fvalue);
    if (value == NULL) {
        return NULL;
    } else if (strncmp(value, HIGH, strlen(HIGH)) == 0) {
        pin->value_hi = true;
    } else if (strncmp(value, LOW, strlen(LOW)) == 0) {
        pin->value_hi = false;
    }
    free(value);

    return pin;
}

/* Remove a pin when you're done with it. The deconstructor first removes the pin from
 * the filesystem using /sysfs/class/gpio/unexport, then frees all of the memory.
 */
int deconstruct_pin(Pin* pin_ptr) {
    if (write_to_file(pin_ptr->snum, UNEXPORT) != EXIT_SUCCESS) {
        perror("failure to unexport pin");
        return EXIT_FAILURE;
    }

    free((void*)pin_ptr->snum);
    free((void*)pin_ptr->fdesc);
    free((void*)pin_ptr->fdirec);
    free((void*)pin_ptr->fvalue);
    free((void*)pin_ptr->fedge);
    free((void*)pin_ptr->factive_low);
    free(pin_ptr);
    return EXIT_SUCCESS;
}
