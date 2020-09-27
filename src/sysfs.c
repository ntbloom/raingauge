#include "sysfs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
