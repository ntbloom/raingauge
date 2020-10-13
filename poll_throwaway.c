#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

/* figure out how poll works in this scenario
 * current setup:
 *      gpio18 -> out high
 *      gpio21 -> in
 *      gpio21/edge -> rising
 *      switch works as interrupt, temporarily switching gpio21 from 0 to 1 and back
 */

int main(void) {
    static int fd;

    const char* val = "/sys/class/gpio/gpio21/value";
    fd = open(val, O_RDONLY);
    if (fd < 0) {
        perror("can't open value");
        return EXIT_FAILURE;
    }

    /* do the poll */
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLPRI | POLLERR;
    int ready = poll(fds, 1, 60);
    printf("ready=%d\n", ready);

    while (1) {
        /*
        if (fds[0].revents & POLLPRI == POLLPRI) {
            printf("gpio is hot\n");
        } else if (fds[0].revents & POLLERR == POLLERR) {
            perror("gpio error");
        }
        */
        printf("revents=%d\n", fds[0].revents);
    }
    off_t now = lseek(fd, 0, 0);
    printf("now=%s\n", now);

    /* close the file */
    if (close(fd) != 0) {
        perror("problem closing file");
        return EXIT_FAILURE;
    }

    /* figure out some macros */
    printf("POLLPRI=%d\nPOLLERR=%d\n", POLLPRI, POLLERR);
    return EXIT_SUCCESS;
}
