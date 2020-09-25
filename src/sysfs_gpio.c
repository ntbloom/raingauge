/*
   sysfs_gpio.c
   control gpio pins using sysfs
 */

#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int file_exists(const char *fdesc, int mode, int timeout) {
    /* checks that file <fdesc> is accessible in <mode> mode, with timeout in seconds */
    long i = timeout;
    time_t start = time(0);

    while (time(0) - start <= i) {
        if (access(fdesc, mode) == 0) {
            return 0;
        }
    }
    return -1;
}

int _write_to_file(const char *msg, const char *fdesc) {
    /* write a string to a file */
    if (file_exists(fdesc, W_OK, TIMEOUT) != 0) {
        fprintf(stderr, "unable to access %s\n", fdesc);
        return EXIT_FAILURE;
    }

    FILE *handler = fopen(fdesc, "r+");
    if (!handler) {
        char *err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfopen error on write: %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return EXIT_FAILURE;
    }
    if (fputs(msg, handler) == -1) {
        char *err = malloc(255);
        sprintf(err, "ERROR LINE %d: \n\tfputs error on msg=%s\n", __LINE__, msg);
        perror(err);
        fclose(handler);
        free(err);
        return EXIT_FAILURE;
    }
    if (fclose(handler) == -1) {
        char *err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfclose error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

char *_read_file(const char *fdesc) {
    /* get contents of a file */

    if (file_exists(fdesc, W_OK, TIMEOUT) != 0) {
        fprintf(stderr, "unable to access %s\n", fdesc);
        return "";
    }

    char *contents = malloc(5);
    FILE *handler = fopen(fdesc, "r");
    if (!handler) {
        char *err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfopen error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return "";
    }
    if (fgets(contents, sizeof(contents), handler) == NULL) {
        char *err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfgets error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
    }
    return contents;
}

int export_pin(struct Pin pin) {
    /* export a pin */
    return _write_to_file(pin.num, EXPORT);
}

int unexport_pin(struct Pin pin) {
    /* unexport a pin */
    return _write_to_file(pin.num, UNEXPORT);
}

int set_direction(struct Pin pin, const char *direction) {
    /* set the direction of the pin */
    return _write_to_file(direction, pin.direction);
}

const char *get_direction(struct Pin pin) {
    /*  get the direction of a pin */
    char *direction = _read_file(pin.direction);
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

int set_value(struct Pin pin, const char *value) {
    /* set the value of a pin to high or low */
    return _write_to_file(value, pin.value);
}

const char *get_value(struct Pin pin) {
    /* value of the pin */
    char *value = _read_file(pin.value);
    if (strncmp(value, HIGH, strlen(HIGH)) == 0) {
        free(value);
        return HIGH;
    } else if (strncmp(value, LOW, strlen(LOW)) == 0) {
        free(value);
        return LOW;
    }
    free(value);
    return "";
}
