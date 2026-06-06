#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <libpq-fe.h>

typedef struct {
    char subject[256];
    char from[256];
    char body[256];
} Email;

int send_email(const char *to, const Email *email);
Email compose_email(void);
#endif