#ifndef MQTT_MESSAGES_H
#define MQTT_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ISO8601 "%Y-%m-%dT%H:%M:%S%z"
#define ISO8601_LEN 25

/* get a timestamp string */
char* make_timestamp(size_t, const char*);

#endif
