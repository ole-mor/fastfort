#ifndef SOCKETS_H
#define SOCKETS_H

#include "config.h"

typedef struct socket_server socket_server_t;
typedef struct socket_client socket_client_t;

socket_server_t socket_server_create(socket_config_t* conf);
int socket_server_run(socket_server_t *server);
void socket_server_clean(socket_server_t *server);

socket_client_t socket_client_create(socket_config_t *conf);
int socket_client_connect(socket_client_t *client);
void sokcet_client_close(sokcet_client_t *client);

#endif

