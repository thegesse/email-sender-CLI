cmake_minimum_required(VERSION 4.1)
project(email_sender_CLI C)

set(CMAKE_C_STANDARD 23)

add_executable(email_sender_CLI main.c
        database-connection/connection.c
        database-connection/connection.h
        querries/sql_queries.c
        querries/sql_queries.h)
