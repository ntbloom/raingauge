#include <fcntl.h>
#include <limits.h>
#include <signal.h>
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

int polling(int);

/* poll a file descriptor */
int polling(int fd) {
    int interrupt, results;

    /* do the poll */
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLPRI | POLLERR;
    fds[0].revents = -1;
    printf("events=%d\n", fds[0].events);
    interrupt = poll(fds, 1, -1);
    results = fds[0].revents;

    printf("revents=%d\n", results);
    switch (interrupt) {
        case -1:
            perror("bad poll()");
            return EXIT_FAILURE;
        case 0:
            printf("no interrupt detected\n");
            return EXIT_FAILURE;
        default:
            results = fds[0].revents;
            if ((results & POLLERR) == POLLERR) {
                printf("poll failure\n");
                return EXIT_FAILURE;
            } else if ((results & POLLPRI) == POLLPRI) {
                printf("gpio was activated\n");
                EXIT_SUCCESS;
            }
    }
}

int main(void) {
    const char* val = "/sys/class/gpio/gpio25/value";
    int fd, success;

    fd = open(val, O_RDONLY);
    printf("fd=%d\n", fd);
    if (fd < 0) {
        perror("can't open value");
    }
    /* perform a dummy read */
    char buf[1];
    read(fd, buf, 0);

    success = polling(fd);

    if (close(fd) != 0) {
        perror("problem closing file");
    }

    /* print the bit masks if needed*/
    /*
    puts("");
    printf("POLLPRI=%d\n", POLLPRI);
    printf("POLLERR=%d\n", POLLERR);
    printf("POLLIN=%d\n", POLLIN);
    */

    return EXIT_SUCCESS;
}
