#ifndef MQTT_MESSAGES_H
#define MQTT_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIMESTAMP_FMT "%Y-%m-%dT%H:%M:%S:z"
#define TIMESTAMP_LEN 25

/* make a timestamp string */
char* make_timestamp(void);

#endif
