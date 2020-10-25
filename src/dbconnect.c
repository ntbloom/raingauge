#include "dbconnect.h"

PGconn* dbconnect(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "failure to connect\n");
        return NULL;
    }
    return conn;
}

