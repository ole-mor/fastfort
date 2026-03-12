
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "btr_sockets_config.h"


typedef struct {
    int fd;
    struct pollfd socks[11];
    int num_clients;
    socket_config_t *config;
    char buffer[1024];
} socket_server_t;










////////// OLD ////////////

void apply_socket_options(int sock, socket_option *opts){
    for (int i = 0; opts[i].level != 0; i++) {
        int result = setsockopt(sock, opts[i].level, opts[i].optname,
                                &opts[i].value, sizeof(opts[i].value));
        if (result < 0){
            fprintf(stderr, "Warning: setsockopt(level=%d, opt=%d, val=%d) failed: %s\n",
                    opts[i].level, opts[i].optname, opts[i].value, strerror(errno));        
        }
    }
}

int create_btr_socket(socket_option* opts) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }
    apply_socket_options(sock, opts);
    return sock;
}

// going to refactor this to use clean code principles.
int btr_socket_server(void){
    struct sockaddr_in client_addr;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(8080)
    };
    
    socklen_t len = sizeof(client_addr);
    const uint8_t backlog = 5;
    char buffer[1024];

    int sock = create_btr_socket(tcp_interactive);
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, backlog);

    struct pollfd socks[11]; // server + 10 clients
    socks[0].fd = sock;
    socks[0].events = POLLIN;
    int num_clients = 0;

    while(1){
        poll(socks, num_clients + 1, -1);

        if (socks[0].revents & POLLIN){
            int client_sock = accept(sock, (struct sockaddr *)&client_addr, &len);
            socks[num_clients + 1].fd = client_sock;
            socks[num_clients + 1].events = POLLIN;
            num_clients++;
        }

        for (int s_idx = 1; s_idx <= num_clients; s_idx++){
            if (socks[s_idx].revents & POLLIN) {
                int bytes = read(socks[s_idx].fd, buffer, 1023);
                if (bytes <= 0) close(socks[s_idx].fd);
                else {
                    for (int r_idx = 1; r_idx <= num_clients; r_idx++){
                        if (s_idx != r_idx) send(socks[r_idx].fd, buffer, bytes, 0);
                    }
                }
            }
        }
    }
    close(sock);
}

