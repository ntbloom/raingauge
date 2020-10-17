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

int poll_one(int);
int prep_file(const char*);

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

/* poll a single file descriptor indefinitely on POLLPRI and POLLERR */
int poll_one(int fd) {
    int interrupt, results;
    struct pollfd fds[1];

    fds[0].fd = fd;
    fds[0].events = POLLPRI | POLLERR;
    fds[0].revents = -1;
    interrupt = poll(fds, 1, -1);
    results = fds[0].revents;

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
                printf("gpio was activated\n");
                EXIT_SUCCESS;
            } else
                return EXIT_FAILURE;
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        return EXIT_FAILURE;
    }
    rd = read(fd, buf, 0);
}

int main(void) {
    const char* value = "/sys/class/gpio/gpio25/value";
    int fd, interrupt, count;

    fd = prep_file(value);
    if (fd == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    count = 10;
    while (count != 0) {
        interrupt = poll_one(fd);
        count--;
    }

    if (close(fd) != 0) {
        perror("problem closing file");
    }
    return EXIT_SUCCESS;
}
