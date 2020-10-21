#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

/* figure out how poll works in this scenario
 * current setup:
 *      gpio18 -> out high
 *      gpio25 -> in
 *      gpio25/edge -> rising
 *      physical switch temporarily switches gpio25 between 0 and 1
 *      current verified with multimeter
 */

int prep_file(const char*);
int poll_one(int, int (*)(void));
int poll_loop(const char*, int);
int interrupt_callback(void);

static char buf[1];
static int rd;

/* prep a POSIX file name for polling */
int prep_file(const char* file) {
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    rd = read(fd, buf, 0);
    return fd;
}

/* generic callback function to return on interrupt */
int interrupt_callback(void) {
    printf("interrupt triggered\n");
    return EXIT_SUCCESS;
}

/* poll a single file descriptor indefinitely on POLLPRI and POLLERR */
int poll_one(int fd, int (*callback)(void)) {
    int interrupt, results;
    struct pollfd fds[1];

    fds[0].fd = fd;
    fds[0].events = POLLPRI | POLLERR;
    fds[0].revents = -1;
    interrupt = poll(fds, 1, -1);

    switch (interrupt) {
        case -1:
            perror("bad poll()");
            return EXIT_FAILURE;
        case 0:
            printf("no interrupt detected\n");
            return EXIT_FAILURE;
        default:
            results = fds[0].revents;
            if ((results & POLLPRI) == POLLPRI) {
                callback();
            } else
                return EXIT_FAILURE;
    }
    /* reset fd to beginning of file */
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        return EXIT_FAILURE;
    }
    rd = read(fd, buf, 0);
    return EXIT_SUCCESS;
}

/* poll the loop n number of times, use -1 for infinite loop */
int poll_loop(const char* value, int n) {
    int fd, interrupt;

    if (n < 0) {
        printf("negative numbers not currently supported for poll_loop()\n");
        return EXIT_FAILURE;
    }

    fd = prep_file(value);
    if (fd < 0) {
        return EXIT_FAILURE;
    }
    while (n > 0) {
        interrupt = poll_one(fd, *interrupt_callback);
        if (interrupt != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
        n--;
    }

    if (close(fd) != 0) {
        perror("problem closing file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(void) {
    int n = 10;
    const char* value = "/sys/class/gpio/gpio25/value";
    if (poll_loop(value, n) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
