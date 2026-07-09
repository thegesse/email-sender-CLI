#include <stdio.h>
#include <stdlib.h>
#include "sql_queries.h"
#include "../database-connection/connection.h"

void get_all_emails() {
    PGconn *conn = connect_to_db();
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return; 
    }
    //Change query to fit table
    PGresult *res = PQexec(conn, "SELECT email FROM people");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        printf("%s\n", PQgetvalue(res, i, 0));
    }

    PQclear(res);
    PQfinish(conn);
}

