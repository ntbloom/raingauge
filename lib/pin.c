#include "pin.h"

Pin* construct_pin(size_t number) {
    Pin* pin;
    size_t base_n, num_n, desc_n, direc_n, value_n, edge_n, factive_n;
    char *num, *desc, *direc, *value, *edge, *active_low;

    /* don't allow  illegal */
    if (number > MAX_PIN || number == 4) {
        return NULL;
    };

    /* create the pin, set everything but the value */
    pin = malloc(sizeof(Pin));
    base_n = strlen(SYSFS) + 1;
    if (number < 10) {
        num_n = strlen("GPIOX/");
    } else {
        num_n = strlen("GPIOXX/");
    }
    desc_n = base_n + num_n;
    direc_n = desc_n + strlen("direction");
    value_n = desc_n + strlen("value");
    edge_n = desc_n + strlen("edge");
    factive_n = desc_n + strlen("active_low");

    num = malloc(num_n);
    sprintf(num, "%d", number);
    pin->num = num;

    desc = malloc(desc_n);
    sprintf(desc, SYSFS "gpio%d", number);
    pin->desc = desc;

    direc = malloc(direc_n);
    sprintf(direc, SYSFS "gpio%d/direction", number);
    pin->direc = direc;

    value = malloc(value_n);
    sprintf(value, SYSFS "gpio%d/value", number);
    pin->value = value;

    edge = malloc(edge_n);
    sprintf(edge, SYSFS "gpio%d/edge", number);
    pin->edge = edge;

    active_low = malloc(factive_n);
    sprintf(active_low, SYSFS "gpio%d/active_low", number);
    pin->active_low = active_low;

    /* export the pin */
    if (write_to_file(EXPORT, num) != EXIT_SUCCESS) {
        fprintf(stderr, "failure to export pin %s to %s\n", num, EXPORT);
        pin = NULL;
        return pin;
    }

    /* make sure all values are accessible before moving forward */
    size_t i, size;
    size = 4;
    char* descriptors[] = {direc, value, edge, active_low};
    for (i = 0; i < size; i++) {
        char* filename = descriptors[i];
        if (file_exists(filename, W_OK, 1) != EXIT_SUCCESS) {
            fprintf(stderr, "failure to access `%s`", filename);
            pin = NULL;
            return pin;
        }
    }
    return pin;
}

int deconstruct_pin(Pin* pin) {
    if (write_to_file(UNEXPORT, pin->num) != EXIT_SUCCESS) {
        fprintf(stderr, "failure to unexport pin %s\n", pin->num);
        return EXIT_FAILURE;
    }

    free((void*)pin->num);
    free((void*)pin->desc);
    free((void*)pin->direc);
    free((void*)pin->value);
    free((void*)pin->edge);
    free((void*)pin->active_low);
    free(pin);
    return EXIT_SUCCESS;
}

int prep_pin(Pin* pin, const char* direc, const char* edge, const char* active_low) {
    if (write_to_file(pin->direc, direc) != EXIT_SUCCESS) {
        fprintf(stderr, "failure to set direction: \n`%s` to `%s`\n", pin->direc, direc);
        return EXIT_FAILURE;
    }
    if (write_to_file(pin->edge, edge) != EXIT_SUCCESS) {
        fprintf(stderr, "failure to set edge: `%s` to `%s`\n", pin->edge, edge);
        return EXIT_FAILURE;
    }
    if (write_to_file(pin->active_low, "1") != EXIT_SUCCESS) {
        fprintf(stderr, "failure to set active_low: `%s` to `%s`\n", pin->active_low, active_low);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
