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
    return seconds;
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

Message* _generic_message(char* topic_base, char* gauge, char* data) {
    Message* msg;
    char *topic, *payload;

    topic = calloc(strlen(gauge) + strlen(topic_base) + 1, sizeof(char));
    strncpy(topic, topic_base, strlen(topic_base) + 1);
    strncat(topic, gauge, strlen(gauge));

    payload = calloc(strlen(data) + 1, sizeof(char));
    strcpy(payload, data);

    msg = construct_message(topic, payload);
    return msg;
}

Message* message_rain(char* gauge, char* amt) {
    return _generic_message(TOPIC_RAIN_BASE, gauge, amt);
}

Message* message_status(char* gauge) {
    char* uptime;

    uptime = get_uptime();
    return _generic_message(TOPIC_STATUS_BASE, gauge, uptime);
}
