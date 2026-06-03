#include <stdio.h>
#include <stdlib.h>
#include "sql_queries.h"
#include "../database-connection/connection.h"

PGconn *conn = connect_to_db();
if (conn == NULL) return 1;

