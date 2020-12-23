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

char* get_uptime(void) {
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

    seconds = calloc(i + 1, sizeof(char));
    strncpy(seconds, intermed, i);
    free(intermed);
    if (seconds) {
        return seconds;
    }
    return NULL;
}
