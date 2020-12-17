#ifndef MQTT_MESSAGES_H
#define MQTT_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ISO8601 "%Y-%m-%dT%H:%M:%S%z"
#define ISO8601_LEN 25
#define UPTIME_LEN 16
#define PROC_UPTIME "/proc/uptime"

/* get the current time as a string in ISO8601 format */
char* make_timestamp(size_t, const char*);

/* get system uptime in seconds since last reboot as string */
char* uptime(void);

#endif
