#ifndef CONSTANTS_H
#define CONSTANTS_H

/* File descriptors for general GPIO usage */
#define SYSFS "/sys/class/gpio/"             // base directory
#define EXPORT "/sys/class/gpio/export"      // to export pin
#define UNEXPORT "/sys/class/gpio/unexport"  // to unexport pin

/* General sysfs instruction values */
#define IN "in"    // for /sys/class/gpio/gpio<n>/direction
#define OUT "out"  // for /sys/class/gpio/gpio<n>/direction
#define HIGH "1"   // for /sys/class/gpio/gpio<n>/value
#define LOW "0"    // for /sys/class/gpio/gpio<n>/value

/* All numbers between 0 and MAX_PIN are legal for GPIO usage on Raspberry Pi 3B. Since
 * constructor takes a size_t, we only check the upper bounds
 */
#define MAX_PIN 26  // highest legal pin number

#endif
