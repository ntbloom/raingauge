#include "mqtt_messages.h"

char* make_timestamp(size_t len, const char* fmt) {
    time_t now;
    char* timestamp;

    time(&now);
    timestamp = malloc(len);

    struct tm* timestruct = localtime(&now);
    strftime(timestamp, len, fmt, timestruct);
    return timestamp;
}
