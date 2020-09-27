#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYSFS_H
#define SYSFS_H

/*  Use this module to read and write to files in small quantities.  Uses short strings
 * like "in" or "out" with a variable but limited length, so these methods are not meant
 * to be used for general file reading.
 */
int write_to_file(const char*, const char*);
char* read_file(const char*);
int file_exists(const char*, int, int);

#endif
