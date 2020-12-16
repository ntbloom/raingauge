#include "mqtt_messages.h"

char* make_timestamp(void) {
    time_t now;
    char* timestamp;

    time(&now);
    timestamp = malloc(TIMESTAMP_LEN);

    struct tm* timestruct = localtime(&now);
    strftime(timestamp, TIMESTAMP_LEN, ISO8601, timestruct);
    return timestamp;
}
