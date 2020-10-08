#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

/* figure out how epoll works in this scenario
 * current setup:
 *      gpio18 -> out high
 *      gpio21 -> in
 *      switch works as interrupt, temporarily switching gpio21 from 0 to 1 and back
 */

int main(void) {
    struct epoll_event ev;
    int epollfd;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    // TODO: wtf?

    return EXIT_SUCCESS;
}
