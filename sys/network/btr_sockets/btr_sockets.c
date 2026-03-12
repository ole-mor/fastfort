
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "btr_sockets_config.h"


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

int create_btr_socket(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }
    apply_socket_options(sock, tcp_interactive);
    return sock;
}


int btr_sockets_config(){
}


