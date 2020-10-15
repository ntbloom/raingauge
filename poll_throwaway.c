#include <fcntl.h>
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

#define MAX_INTERRUPT 600000

int main(void) {
    int fd, interrupt;

    const char* val = "/sys/class/gpio/gpio25/value";
    fd = open(val, O_RDONLY);
    if (fd < 0) {
        perror("can't open value");
        return EXIT_FAILURE;
    }

    /* do the poll */
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLPRI | POLLERR;
    fds[0].revents = 0;
    interrupt = poll(fds, 1, -1);

    /*
    for (;;) {
        if (fds[0].revents & POLLPRI == POLLPRI) {
            printf("gpio is hot\n");
            return EXIT_SUCCESS;
        } else if (fds[0].revents & POLLERR == POLLERR) {
            perror("poll failure");
            return EXIT_FAILURE;
        }
    }
    */

    if (close(fd) != 0) {
        perror("problem closing file");
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
