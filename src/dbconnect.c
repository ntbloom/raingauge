#include "dbconnect.h"

#define SETS "INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id ="
#define GETS "SELECT SUM(num) FROM ticks WHERE gauge ="

PGconn* dbconnect(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "failure to connect: %s\n", PQerrorMessage(conn));
        return NULL;
    }
    return conn;
}

/* add a click to the database for the gauge */
int add_tick(PGconn* conn, int gauge) {
    char command[255];
    sprintf(command, SETS " %d", gauge);
    PGresult* res = PQexec(conn, command);
    ExecStatusType status = PQresultStatus(res);
    if (status != PGRES_COMMAND_OK) {
        fprintf(stderr, "error inserting click: %s", PQresStatus(status));
        PQclear(res);
        return EXIT_FAILURE;
    }
    PQclear(res);
    return EXIT_SUCCESS;
}

/* returns all clicks for a gauge for alltime */
double all_ticks(PGconn* conn, int gauge) {
    double value;
    char command[255];
    sprintf(command, GETS " %d", gauge);
    PGresult* res = PQexec(conn, command);
    ExecStatusType status = PQresultStatus(res);
    if (status != PGRES_TUPLES_OK) {
        fprintf(stderr, "error retrieving clicks: %s", PQresStatus(status));
        value = -1.0;
    } else {
        const char* strval = PQgetvalue(res, 0, 0);
        value = atof(strval);
        if (value == 0 && strncmp(strval, "0.0", 2) != 0) {
            value = -1.0;
        }
    }
    PQclear(res);
    return value;
}

