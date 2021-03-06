#include "sysfs.h"

/* write a string to a file */
int write_to_file(const char* fdesc, const char* msg) {
    if (file_exists(fdesc, W_OK, 1) != 0) {
        fprintf(stderr, "file `%s` does not exist\n", fdesc);
        return EXIT_FAILURE;
    }

    FILE* handler = fopen(fdesc, "r+");
    if (!handler) {
        fprintf(stderr, "fopen error on %s\n", fdesc);
        return EXIT_FAILURE;
    }
    if (fputs(msg, handler) == EOF) {
        fprintf(stderr, "fputs error on %s\n", fdesc);
        return EXIT_FAILURE;
    }
    if (fclose(handler) == EXIT_FAILURE) {
        fprintf(stderr, "fclose error on %s\n", fdesc);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* get contents of a file */
char* read_file(const char* fdesc) {
    char* contents = malloc(5);
    FILE* handler = fopen(fdesc, "r");
    if (!handler) {
        fprintf(stderr, "fopen error on %s\n", fdesc);
        free(contents);
        return NULL;
    }
    if (fgets(contents, sizeof(contents), handler) == NULL) {
        fprintf(stderr, "fgets error on %s\n", fdesc);
    }
    if (fclose(handler) == EXIT_FAILURE) {
        fprintf(stderr, "fclose error on %s\n", fdesc);
        free(contents);
        return NULL;
    }
    return contents;
}

/* Check that file <fdesc> is accessible in <mode> mode, with timeout in seconds. Using
 * sysfs for GPIO in a fast language like C, there are possible race conditions on file
 * permissions, so we set a short timeout (1 second is sufficient) to let things catch up.
 * Set timeout to zero for an immediate checking if you know the permissions are static.
 */
int file_exists(const char* fdesc, int mode, int timeout) {
    if (timeout == 0) {
        if (access(fdesc, mode) == 0) {
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "file %s doesn't exist\n", fdesc);
            return EXIT_FAILURE;
        }
    }
    long i = timeout;
    time_t start = time(0);
    while (time(0) - start <= i) {
        if (access(fdesc, mode) == 0) {
            return EXIT_SUCCESS;
        }
    }
    fprintf(stderr, "file %s isn't accessible in %d mode\n", fdesc, mode);
    return EXIT_FAILURE;
}
