#ifndef CONNECTION_H
#define CONNECTION_H

#include <libpq-fe.h>

PGconn* connect_to_db();

#endif