#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "email_sender.h"

Email compose_email(void) {
    Email email = {0};
    char line[1024];

    printf("Subject: ");
    fgets(email.subject, sizeof(email.subject), stdin);
    email.subject[strcspn(email.subject, "\n")] = 0;

    printf("From (email): ");
    fgets(email.from, sizeof(email.from), stdin);
    email.from[strcspn(email.from, "\n")] = 0;

    printf("Body: ");
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "\n") == 0) break;
        if (strlen(email.body) + strlen(line) < sizeof(email.body) - 1) {
            strcat(email.body, line);
        }
    }
    return email;
}

int send_email(const char *to, const Email *email) {
    char cmd[8192];

    snprintf(cmd, sizeof(cmd), "msmtp -t %s", to);

    FILE *pipe = popen(cmd, "w");
    if (!pipe) {
        perror("msmtp failed");
        return -1;
    }

    //header
    fprintf(pipe, "To: %s\n", to);
    fprintf(pipe, "Subject: %s\n", email->subject);
    if (strlen(email->from) > 0) {
        fprintf(pipe, "From: %s\n", email->from);
    }
    fprintf(pipe, "\n");  // blank line separates headers from body
    fprintf(pipe, "%s", email->body);

    int status = pclose(pipe);

    if (status == 0) {
        printf("Sent to: %s\n", to);
    } else {
        fprintf(stderr, "Failed to send to: %s (exit code: %d)\n", to, status);
    }

    usleep(100000);
    return status;
}