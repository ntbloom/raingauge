#include "dbconnect.h"

PGconn* dbconnect(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "failure to connect: %s\n", PQerrorMessage(conn));
        return NULL;
    }
    return conn;
}

