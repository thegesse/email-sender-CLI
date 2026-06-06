#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "email/email_sender.h"
#include "queries/sql_queries.h"
#include "database-connection/connection.h"

int main(void) {
    Email email = compose_email();

    printf("Connecting to db...\n");
    PGconn *conn = connect_to_db();
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "DB connection failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }
    printf("Connected to db, running query...\n");

    PGresult *res = PQexec(conn, "SELECT email FROM people WHERE email IS NOT NULL");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQresultErrorMessage(res));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    int rows = PQntuples(res);
    printf("Found %d recipients.\n\n", rows);

    printf("Sending emails...\n");
    for (int i = 0; i < rows; i++) {
        const char *addr = PQgetvalue(res, i, 0);
        if (strchr(addr, '@')) {
            send_email(addr, &email);
        }
    }

    printf("\nDone.\n");
    PQclear(res);
    PQfinish(conn);
    return 0;
}