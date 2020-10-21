#ifndef POLL_H
#define POLL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

/* get a file descriptor from a sysfs filename */
int prep_file(const char*);

/* poll a single file descriptor indefinitely on POLLPRI and POLLERR */
int poll_one(int, int (*)(void));

/* poll the loop n number of times, use -1 for infinite loop */
int poll_loop(const char*, int);

/* generic callback function to return on interrupt */
int interrupt_callback(void);

#endif
