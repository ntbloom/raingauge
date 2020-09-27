#ifndef CONSTANTS_H
#define CONSTANTS_H

/* global variable constants to be shared throught the program, typically things like
 * filepaths that are not likely to change
 */

#define SYSFS "/sys/class/gpio/"             // base directory
#define EXPORT "/sys/class/gpio/export"      // to export pin
#define UNEXPORT "/sys/class/gpio/unexport"  // to unexport pin
#define IN "in"                              // for /sys/class/gpio/gpio<n>/direction
#define OUT "out"                            // for /sys/class/gpio/gpio<n>/direction
#define HIGH "1"                             // for /sys/class/gpio/gpio<n>/value
#define LOW "0"                              // for /sys/class/gpio/gpio<n>/value
#define MAX_PIN 40                           // highest legal pin number

#endif
