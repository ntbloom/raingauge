#include "../include/poll.h"

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

int interrupt_callback(void) {
    printf("interrupt triggered\n");
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
    fds[1].events = 0;

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
            } else if (fds[1].revents != 0) {
                printf("breaking out of loop early!\n");
                return 2;
            } else
                return EXIT_FAILURE;
    }
    /* reset fd_good to beginning of file */
    if (lseek(fd_good, 0, SEEK_SET) == -1) {
        perror("lseek");
        return EXIT_FAILURE;
    }
    rd = read(fd_good, buf, 0);
    return EXIT_SUCCESS;
}

int poll_loop(const char* value, const char* breakout, int n) {
    int fd_value, fd_breakout, interrupt, quit;

    if (n < 0) {
        printf("negative numbers not currently supported for poll_loop()\n");
        return EXIT_FAILURE;
    }

    fd_value = prep_file(value);
    fd_breakout = prep_file(breakout);
    if (fd_value < 0 || fd_breakout < 0) {
        return EXIT_FAILURE;
    }

    /* main loop */
    quit = 0;
    while (quit != 1) {
        interrupt = poll_one(fd_value, fd_breakout, *interrupt_callback);
        switch (interrupt) {
            /* loop was cancelled by outside event */
            case 2:
                quit = 1;
                break;
            case EXIT_FAILURE:
                quit = 1;
                if (close(fd_value) != 0 || close(fd_breakout) != 0) {
                    fprintf(stderr, "problem closing files %s, %s", value, breakout);
                    return EXIT_FAILURE;
                }
            default:
                continue;
        }
    }

    if (close(fd_value) != 0 || close(fd_breakout) != 0) {
        fprintf(stderr, "problem closing files %s, %s", value, breakout);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

