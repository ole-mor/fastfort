#include "sockets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <termios.h>

int create_udp_socket(void) {
    int file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (file_descriptor == -1) { perror("socket error"); exit(1); }
    return file_descriptor;
}

int send_to(int file_descriptor, const char *message, struct sockaddr_in *dest) {
    int bytes = sendto(file_descriptor, message, strlen(message), 0,
                       (struct sockaddr *)dest, sizeof(*dest));
    if (bytes < 0) perror("send_to error");
    return bytes;
}

int receive_from(int file_descriptor, char *buffer, int buffer_size, struct sockaddr_in *sender) {
    socklen_t len = sizeof(*sender);
    memset(buffer, 0, buffer_size);
    int bytes = recvfrom(file_descriptor, buffer, buffer_size - 1, 0,
                         (struct sockaddr *)sender, &len);
    if (bytes < 0) perror("receive_from error");
    return bytes;
}

int create_tcp_socket(void) {
    int file_descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
    if (file_descriptor == -1) { perror("socket error"); exit(1); }
    int opt = 1;
    setsockopt(file_descriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    return file_descriptor;
}

void bind_socket(int file_descriptor, struct sockaddr_in *addr, int port) {
    addr->sin_family      = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port        = htons(port);
    if (bind(file_descriptor, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("bind error");
        exit(1);
    }
}

void start_listening(int file_descriptor, int backlog) {
    if (listen(file_descriptor, backlog) < 0) { perror("listen error"); exit(1); }
}

int accept_client(int file_descriptor, struct sockaddr_in *client_addr) {
    socklen_t len = sizeof(*client_addr);
    int client_file_descriptor = accept(file_descriptor, (struct sockaddr *)client_addr, &len);
    if (client_file_descriptor < 0) { perror("accept error"); exit(1); }
    return client_file_descriptor;
}

void connect_to_server(int file_descriptor, struct sockaddr_in *addr, const char *ip, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port   = htons(port);
    if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }
    if (connect(file_descriptor, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("connect error");
        exit(1);
    }
}

int send_message(int file_descriptor, const char *message) {
    int bytes = send(file_descriptor, message, strlen(message), 0);
    if (bytes < 0) perror("send error");
    return bytes;
}

int receive_message(int file_descriptor, char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size);
    int bytes = read(file_descriptor, buffer, buffer_size - 1);
    if (bytes < 0) perror("read error");
    return bytes;
}

void close_socket(int file_descriptor) {
    close(file_descriptor);
}

int socket_server(void) {
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    int server_file_descriptor = create_tcp_socket();
    bind_socket(server_file_descriptor, &server_addr, 8080);
    start_listening(server_file_descriptor, 5);
    while (1) {
        int client_file_descriptor = accept_client(server_file_descriptor, &client_addr);
        receive_message(client_file_descriptor, buffer, 1024);
        send_message(client_file_descriptor, buffer);
        close_socket(client_file_descriptor);
    }
    close_socket(server_file_descriptor);
    return 0;
}

int socket_client(void) {
    struct sockaddr_in server_addr;
    char buffer[1024];
    int sock_file_descriptor = create_tcp_socket();
    connect_to_server(sock_file_descriptor, &server_addr, "127.0.0.1", 8080);
    send_message(sock_file_descriptor, "AA");
    receive_message(sock_file_descriptor, buffer, 1024);
    close_socket(sock_file_descriptor);
    return 0;
}

int open_serial(const char *port, int baud) {
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) { perror("open_serial error"); exit(1); }
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |=  CS8;
    options.c_cflag |=  CREAD | CLOCAL;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSANOW, &options);
    return fd;
}

int read_serial(int fd, char *buffer, int size) {
    int bytes = read(fd, buffer, size - 1);
    if (bytes < 0) perror("read_serial error");
    else buffer[bytes] = '\0';
    return bytes;
}

int write_serial(int fd, const char *data) {
    int bytes = write(fd, data, strlen(data));
    if (bytes < 0) perror("write_serial error");
    return bytes;
}

void close_serial(int fd) {
    close(fd);
}

void serial_to_socket_bridge(const char *serial_port, int baud, int tcp_port) {
    char buffer[1024];
    int serial_fd = open_serial(serial_port, baud);
    struct sockaddr_in server_addr, client_addr;
    int server_fd = create_tcp_socket();
    bind_socket(server_fd, &server_addr, tcp_port);
    start_listening(server_fd, 5);
    int client_fd = accept_client(server_fd, &client_addr);
    fd_set read_fds;
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(serial_fd, &read_fds);
        FD_SET(client_fd, &read_fds);
        int max_fd = serial_fd > client_fd ? serial_fd : client_fd;
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select error");
            break;
        }
        if (FD_ISSET(serial_fd, &read_fds)) {
            int bytes = read_serial(serial_fd, buffer, sizeof(buffer));
            if (bytes > 0) send_message(client_fd, buffer);
        }
        if (FD_ISSET(client_fd, &read_fds)) {
            int bytes = receive_message(client_fd, buffer, sizeof(buffer));
            if (bytes > 0) write_serial(serial_fd, buffer);
            else break;
        }
    }
    close_serial(serial_fd);
    close_socket(client_fd);
    close_socket(server_fd);
}

void serial_to_udp_bridge(const char *serial_port, int baud, int udp_port) {
    char buffer[1024];
    int serial_fd = open_serial(serial_port, baud);
    struct sockaddr_in addr, sender;
    int udp_fd = create_udp_socket();
    bind_socket(udp_fd, &addr, udp_port);

    fcntl(udp_fd,   F_SETFL, O_NONBLOCK);
    fcntl(serial_fd, F_SETFL, O_NONBLOCK);

    while (1) {
        int serial_bytes = read_serial(serial_fd, buffer, sizeof(buffer));
        if (serial_bytes > 0)
            send_to(udp_fd, buffer, &sender);

        int udp_bytes = receive_from(udp_fd, buffer, sizeof(buffer), &sender);
        if (udp_bytes > 0)
            write_serial(serial_fd, buffer);
    }

    close_serial(serial_fd);
    close_socket(udp_fd);
}
