#include "connection.h"
#include <stdlib.h>
#include <stdio.h>

PGconn* connect_to_db() {
    const char *conninfo = getenv("DATABASE_URL");

    if (conninfo == NULL) {
        fprintf(stderr, "DATABASE_URL not set\n");
        return NULL;
    }

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "PQstatus(conn) failed\n");
        PQfinish(conn);
        return NULL;
    }

    return conn;
}