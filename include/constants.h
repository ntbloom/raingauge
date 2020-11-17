#ifndef CONSTANTS_H
#define CONSTANTS_H

/* File descriptors for general GPIO usage */
#define SYSFS "/sys/class/gpio/"             // base directory
#define EXPORT "/sys/class/gpio/export"      // to export pin
#define UNEXPORT "/sys/class/gpio/unexport"  // to unexport pin

/* General sysfs instruction values */
#define IN "in"            // for /sys/class/gpio/gpio<n>/direction
#define OUT "out"          // for /sys/class/gpio/gpio<n>/direction
#define HIGH "1"           // for /sys/class/gpio/gpio<n>/value
#define LOW "0"            // for /sys/class/gpio/gpio<n>/value
#define RISING "rising"    // for /sys/class/gpio/gpio<n>/edge
#define FALLING "falling"  // for /sys/class/gpio/gpio<n>/edge
#define BOTH "both"        // for /sys/class/gpio/gpio<n>/edge
#define NONE "none"        // for /sys/class/gpio/gpio<n>/edge

/* All numbers between 0 and MAX_PIN are legal for GPIO usage on Raspberry Pi 3B. Since
 * constructor takes a size_t, we only check the upper bounds
 */
#define MAX_PIN 26   // highest legal pin number
#define GAUGE_RX 25  // pin receiving power from 5v pin
#define STOP_TX 18   // pin sending power to kill
#define STOP_RX 23   // pin receiving power to kill

#endif
