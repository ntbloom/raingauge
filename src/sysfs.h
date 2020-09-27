#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYSFS_H
#define SYSFS_H

#define TIMEOUT 1

/* helper functions */
int write_to_file(const char*, const char*);
char* read_file(const char*);
int file_exists(const char*, int, int);

#endif
