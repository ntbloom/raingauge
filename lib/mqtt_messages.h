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

#define TOPIC_RAIN_BASE "v1/rain/"
#define MESSAGE_STATUS_BASE "v1/status/"

/* get the current time as a string in ISO8601 format */
char* get_timestamp();

/* get system uptime in seconds since last reboot as string */
char* get_uptime(void);

/* struct for passing along mqtt messages and topics, along with constructor and deconstructor */
typedef struct Message Message;
struct Message {
    char* topic;
    char* timestamp;
    char* payload;
};
Message* construct_message(char*, char*);
int deconstruct_message(Message*);

/* make a rain event */
Message* message_rain(const char*, const char*);

#endif
