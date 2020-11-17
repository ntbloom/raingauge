#include "../include/poll.h"

static char buf[1];
static int rd;
static int count = 0;

/* prep a POSIX file name for polling */
int prep_file(const char* file) {
    int fd;

    fd = open(file, O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "problem opening %s\n", file);
        return EXIT_FAILURE;
    }
    rd = read(fd, buf, 0);
    return fd;
}

/* generic callback on an interrupt, replace with database call in prod */
int generic_callback(void) {
    printf("interrupt triggered: clicks = %d\n", count++ + 1);
    return EXIT_SUCCESS;
}

/* return 0 for good, 1 for error, 2 for break early */
int poll_one(int fd_good, int fd_break, int (*callback)(void)) {
    int interrupt;
    struct pollfd fds[2];

    fds[0].fd = fd_good;
    fds[0].events = POLLPRI | POLLERR;

    /* declare a second file descriptor to close loop from outside the function */
    fds[1].fd = fd_break;
    fds[1].events = POLLPRI | POLLERR;

    interrupt = poll(fds, 2, -1);

    switch (interrupt) {
        case -1:
            fprintf(stderr, "bad use of poll()\n");
            return EXIT_FAILURE;
        case 0:
            fprintf(stderr, "no interrupt detected\n");
            return EXIT_FAILURE;
        default:
            /* interrupt detected on the good pin */
            if ((fds[0].revents & POLLPRI) == POLLPRI) {
                callback();
            } else if ((fds[1].revents & POLLPRI) == POLLPRI) {
                printf("stopping GPIO poll...\n");
                return 2;
            } else
                return EXIT_FAILURE;
    }
    /* reset fd_good to beginning of file */
    if (lseek(fd_good, 0, SEEK_SET) == -1) {
        fprintf(stderr, "problem with lseek on file descriptor %d\n", fd_good);
        return EXIT_FAILURE;
    }
    rd = read(fd_good, buf, 0);
    return EXIT_SUCCESS;
}

int poll_loop(const char* value, const char* breakout, int (*callback)(void)) {
    int fd_value, fd_breakout, interrupt, quit;
    int (*cb)(void);

    /* default to generic_callback unless one is specified */
    if (callback == NULL) {
        cb = *generic_callback;
    } else {
        cb = *callback;
    }

    fd_value = prep_file(value);
    fd_breakout = prep_file(breakout);
    if (fd_value < 0 || fd_breakout < 0) {
        return EXIT_FAILURE;
    }

    /* main loop */
    quit = 0;
    while (quit != 1) {
        interrupt = poll_one(fd_value, fd_breakout, cb);
        switch (interrupt) {
            case 2: /* loop was cancelled by outside event */
                quit = 1;
                break;
            case EXIT_FAILURE: /* problem in the poll function */
                quit = 1;
                if (close(fd_value) != 0 || close(fd_breakout) != 0) {
                    fprintf(stderr, "problem closing files %s, %s", value, breakout);
                    return EXIT_FAILURE;
                }
            default: /* continue the infinite loop */
                continue;
        }
    }

    if (close(fd_value) != 0 || close(fd_breakout) != 0) {
        fprintf(stderr, "problem closing files %s, %s", value, breakout);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

