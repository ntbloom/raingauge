#include "mqtt_messages.h"

char* get_timestamp() {
    time_t now;
    char* timestamp;
    size_t len;

    len = ISO8601_LEN;
    time(&now);
    timestamp = malloc(len);

    struct tm* timestruct = localtime(&now);
    strftime(timestamp, len, ISO8601, timestruct);
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

Message* construct_message(char* topic, char* payload) {
    Message* msg;
    msg = malloc(sizeof(Message));
    msg->topic = topic;
    msg->timestamp = get_timestamp();
    msg->payload = payload;

    return msg;
}

int deconstruct_message(Message* msg) {
    free((void*)msg->topic);
    free((void*)msg->timestamp);
    free((void*)msg->payload);
    free(msg);
    return EXIT_SUCCESS;
}

Message* message_rain(const char* gauge, const char* amt) {
    Message* msg;
    char *topic, *payload;

    topic = calloc(strlen(gauge) + strlen(TOPIC_RAIN_BASE) + 1, sizeof(char));
    strncpy(topic, TOPIC_RAIN_BASE, strlen(TOPIC_RAIN_BASE) + 1);
    strncat(topic, gauge, strlen(gauge));

    payload = calloc(strlen(amt) + 1, sizeof(char));
    strcpy(payload, amt);

    msg = construct_message(topic, payload);
    return msg;
}
