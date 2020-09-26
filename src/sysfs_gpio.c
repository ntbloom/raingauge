#include "sysfs_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* create a new Pin */
Pin* construct_pin(int number) {
    Pin* p = NULL;
    return p;
}

/* deconstruct a Pin */
int deconstruct_pin(Pin* pin) {
    // do some stuff
    return EXIT_SUCCESS;
}

/* check that file <fdesc> is accessible in <mode> mode, with timeout in seconds */
int file_exists(const char* fdesc, int mode, int timeout) {
    long i = timeout;
    time_t start = time(0);

    while (time(0) - start <= i) {
        if (access(fdesc, mode) == 0) {
            return 0;
        }
    }
    return -1;
}

/* write a string to a file */
int write_to_file(const char* msg, const char* fdesc) {
    if (file_exists(fdesc, W_OK, TIMEOUT) != 0) {
        fprintf(stderr, "unable to access %s\n", fdesc);
        return EXIT_FAILURE;
    }

    FILE* handler = fopen(fdesc, "r+");
    if (!handler) {
        char* err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfopen error on write: %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return EXIT_FAILURE;
    }
    if (fputs(msg, handler) == -1) {
        char* err = malloc(255);
        sprintf(err, "ERROR LINE %d: \n\tfputs error on msg=%s\n", __LINE__, msg);
        perror(err);
        fclose(handler);
        free(err);
        return EXIT_FAILURE;
    }
    if (fclose(handler) == -1) {
        char* err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfclose error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* get contents of a file */
char* read_file(const char* fdesc) {
    if (file_exists(fdesc, W_OK, TIMEOUT) != 0) {
        fprintf(stderr, "unable to access %s\n", fdesc);
        return "";
    }

    char* contents = malloc(5);
    FILE* handler = fopen(fdesc, "r");
    if (!handler) {
        char* err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfopen error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
        return "";
    }
    if (fgets(contents, sizeof(contents), handler) == NULL) {
        char* err = malloc(255);
        sprintf(err, "ERROR LINE %d:\n\tfgets error on %s\n", __LINE__, fdesc);
        perror(err);
        free(err);
    }
    return contents;
}

/* export a pin */
int export_pin(Pin pin) { return write_to_file(pin.num, EXPORT); }

/* unexport a pin */
int unexport_pin(Pin pin) { return write_to_file(pin.num, UNEXPORT); }

/* set the direction of the pin */
int set_direction(Pin pin, const char* direction) {
    return write_to_file(direction, pin.fdirection);
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

/* set the value of a pin to high or low */
int set_value(Pin pin, const char* value) { return write_to_file(value, pin.fvalue); }

/* get value of the pin */
const char* get_value(Pin pin) {
    char* value = read_file(pin.fvalue);
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
