/*Client header file*/
#ifndef TFTP_CLIENT_H
#define TFTP_CLIENT_H

#include "tftp.h"

typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_len;
} tftp_client_t;

// Function prototypes
void connect_server(tftp_client_t *client);
void put_the_file(tftp_client_t *client);
void get_the_file(tftp_client_t *client);
void Mode_Change();
#endif