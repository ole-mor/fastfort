

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
    struct sockaddr_in server_addr;
    socket_config *config;
    char buffer[1024];
} socket_client_t;









//////// OLD /////////

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

int btr_socket_client(void){
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080)
    };
    inet_pton(server_addr.sin_family, "127.0.0.1", &server_addr.sin_addr);
    
    char buffer[1024];
    char message[1024];
    
    int sock = create_btr_socket(tcp_interactive);
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    while(1){
        fgets(message, sizeof(message), stdin);
        send(sock, message, strlen(message), 0);
        memset(buffer, 0, 1024);
        int bytes = read(sock, buffer, 1024 - 1);
        if (bytes > 0)
            printf("%s\n", buffer);
    }
    close(sock);
}


