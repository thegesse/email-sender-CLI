#include "connection.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PGconn* connect_to_db() {
    const char *conninfo = getenv("DATABASE_URL");

    if (conninfo == NULL) {
        fprintf(stderr, "DATABASE_URL not set\n");
        return NULL;
    }

    const char *at = strchr(conninfo, '@');
    if (at) {
        printf("Connecting to: postgresql://***@%s\n", at + 1);
    }

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    printf("Connected successfully.\n");
    return conn;
}