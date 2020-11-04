#include "../include/sysfs.h"

/* write a string to a file */
int write_to_file(const char* fdesc, const char* msg) {
    if (file_exists(fdesc, W_OK, 1) != 0) {
        char* err = malloc(strlen(fdesc) + 50);
        sprintf(err, "file `%s` does not exist", fdesc);
        perror("err");
        free(err);
        return EXIT_FAILURE;
    }

    FILE* handler = fopen(fdesc, "r+");
    if (!handler) {
        perror("write_to_file() fopen error");
        return EXIT_FAILURE;
    }
    if (fputs(msg, handler) == EOF) {
        perror("write_to_file() fputs error");
        return EXIT_FAILURE;
    }
    if (fclose(handler) == EXIT_FAILURE) {
        perror("write_to_file() fclose error");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* get contents of a file */
char* read_file(const char* fdesc) {
    char* contents = malloc(5);
    FILE* handler = fopen(fdesc, "r");
    if (!handler) {
        perror("read_file fopen error");
        free(contents);
        return NULL;
    }
    if (fgets(contents, sizeof(contents), handler) == NULL) {
        perror("fgets");
    }
    if (fclose(handler) == EXIT_FAILURE) {
        perror("read_file() fclose error");
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
    return EXIT_FAILURE;
}
