#include "sysfs.h"
#include <time.h>
#include <unistd.h>
#include "../common/constants.h"

/* write a string to a file */
int write_to_file(const char* msg, const char* fdesc) {
    if (file_exists(fdesc, W_OK, 1) != 0) {
        perror("file does not exist");
        return EXIT_FAILURE;
    }

    FILE* handler = fopen(fdesc, "r+");
    if (!handler) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    if (fputs(msg, handler) == -1) {
        perror("fputs");
        return EXIT_FAILURE;
    }
    if (fclose(handler) == -1) {
        perror("fclose");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* get contents of a file */
char* read_file(const char* fdesc) {
    char* contents = malloc(5);
    FILE* handler = fopen(fdesc, "r");
    if (!handler) {
        perror("fopen");
        return NULL;
    }
    if (fgets(contents, sizeof(contents), handler) == NULL) {
        perror("fgets");
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
