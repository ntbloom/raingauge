#include "pin.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "sysfs.h"

/* create a new Pin */
Pin* construct_pin(size_t number) {
    if (number > MAX_PIN) { /* TODO: catch this error */
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
    if (write_to_file(snum, EXPORT) != EXIT_SUCCESS) { /* TODO: catch this error */
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
