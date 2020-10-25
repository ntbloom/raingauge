#include "dbconnect.h"

PGconn* dbconnect(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        perror("failure to connect");
        return NULL;
    }
    return conn;
}

