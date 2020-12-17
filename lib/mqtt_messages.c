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
    char* seconds;
    seconds = malloc(UPTIME_LEN);
    FILE* handler = fopen(PROC_UPTIME, "r");
    if (!handler) {
        free(seconds);
        fprintf(stderr, "error reading %s\n", PROC_UPTIME);
        return NULL;
    }
    /* TODO: read one char at a time into `seconds` until space */
    int i;
    char c;
    for (i = 0; i < UPTIME_LEN; i++) {
        c = fgetc(handler);
        if (c == ' ') {
            break;
        }
        seconds[i] = c;
    }
    printf("i = %d\n", i);

    if (fclose(handler) == EXIT_FAILURE) {
        free(seconds);
        fprintf(stderr, "error closing %s\n", PROC_UPTIME);
        return NULL;
    }
    return seconds;
}
