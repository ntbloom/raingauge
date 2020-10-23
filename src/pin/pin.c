#include "pin.h"

/* Create a new Pin struct corresponding to a legal GPIO pin. Provide an integer between
 * MIN_PIN and MAX_PIN and the constructor provides the rest, including exporting that
 * number to /sys/class/gpio/export.  By default all pins are set to IN, so we read the
 * value in case it's already receiving data.
 */
Pin* construct_pin(size_t number) {
    /* don't allow  illegal */
    if (number > MAX_PIN || number == 4) {
        return NULL;
    };

    /* create the pin, set everything but the value */
    Pin* pin = malloc(sizeof(Pin));
    size_t base_n = strlen(SYSFS) + 1;
    size_t num_n;
    if (number < 10) {
        num_n = strlen("GPIOX/");
    } else {
        num_n = strlen("GPIOXX/");
    }
    size_t desc_n = base_n + num_n;
    size_t direc_n = desc_n + strlen("direction");
    size_t value_n = desc_n + strlen("value");
    size_t edge_n = desc_n + strlen("edge");
    size_t factive_n = desc_n + strlen("active_low");

    char* num = malloc(num_n);
    sprintf(num, "%d", number);
    pin->num = num;

    char* desc = malloc(desc_n);
    sprintf(desc, SYSFS "gpio%d", number);
    pin->desc = desc;

    char* direc = malloc(direc_n);
    sprintf(direc, SYSFS "gpio%d/direction", number);
    pin->direc = direc;

    char* value = malloc(value_n);
    sprintf(value, SYSFS "gpio%d/value", number);
    pin->value = value;

    char* edge = malloc(edge_n);
    sprintf(edge, SYSFS "gpio%d/edge", number);
    pin->edge = edge;

    char* active_low = malloc(factive_n);
    sprintf(active_low, SYSFS "gpio%d/active_low", number);
    pin->active_low = active_low;

    /* export the pin, block until "value" is ready in the filesystem */
    if (write_to_file(num, EXPORT) != EXIT_SUCCESS) {
        perror("failure to export pin");
        fprintf(stderr, "\tnum=%s\n\tEXPORT=%s\n", num, EXPORT);
        return NULL;
    }
    if (file_exists(value, W_OK, 1) != EXIT_SUCCESS) {
        perror("pin was not exported, no value exists");
        fprintf(stderr, "\tgpio%d\n", number);
        return NULL;
    }
    return pin;
}

/* Remove a pin when you're done with it. The deconstructor first removes the pin from
 * the filesystem using /sysfs/class/gpio/unexport, then frees all of the memory.
 */
int deconstruct_pin(Pin* pin_ptr) {
    if (write_to_file(pin_ptr->num, UNEXPORT) != EXIT_SUCCESS) {
        perror("failure to unexport pin");
        return EXIT_FAILURE;
    }

    free((void*)pin_ptr->num);
    free((void*)pin_ptr->desc);
    free((void*)pin_ptr->direc);
    free((void*)pin_ptr->value);
    free((void*)pin_ptr->edge);
    free((void*)pin_ptr->active_low);
    free(pin_ptr);
    return EXIT_SUCCESS;
}

/* poll a pin
 * TODO: learn how to do this
 */
int poll_pin(Pin* pin_ptr) {
    printf("value is found at %s\n", pin_ptr->value);
    return EXIT_SUCCESS;
}

