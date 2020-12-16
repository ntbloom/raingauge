#include "mqtt_messages.h"

/* returns a string of just a header object */
char* make_timestamp(void) {
    time_t now;
    char* timestamp;
    const char* fmt;
    size_t len;

    time(&now);
    len = 25;
    timestamp = malloc(len);
    fmt = "%Y-%m-%dT%H:%M:%S%z";

    struct tm* timestruct = localtime(&now);
    strftime(timestamp, len, fmt, timestruct);
    return timestamp;
}
