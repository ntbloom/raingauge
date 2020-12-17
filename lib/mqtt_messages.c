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

char* uptime(void) {
    char *intermed, *seconds;
    size_t i;
    char c;

    intermed = malloc(UPTIME_LEN);
    FILE* handler = fopen(PROC_UPTIME, "r");
    if (!handler) {
        free(intermed);
        fprintf(stderr, "error reading %s\n", PROC_UPTIME);
        return NULL;
    }
    for (i = 0; i < UPTIME_LEN; i++) {
        c = fgetc(handler);
        if (c == ' ') {
            break;
        }
        intermed[i] = c;
    }
    if (fclose(handler) == EXIT_FAILURE) {
        free(intermed);
        fprintf(stderr, "error closing %s\n", PROC_UPTIME);
        return NULL;
    }

    seconds = malloc(i + 1);
    strncpy(seconds, intermed, i);
    free(intermed);

    return seconds;
}
