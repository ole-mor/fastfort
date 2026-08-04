#ifndef SOCKETS_H
#define SOCKETS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>

int  create_udp_socket(void);
int  send_to(int file_descriptor, const char *message, struct sockaddr_in *dest);
int  receive_from(int file_descriptor, char *buffer, int buffer_size, struct sockaddr_in *sender);

int  create_tcp_socket(void);
void bind_socket(int file_descriptor, struct sockaddr_in *addr, int port);
void start_listening(int file_descriptor, int backlog);
int  accept_client(int file_descriptor, struct sockaddr_in *client_addr);
void connect_to_server(int file_descriptor, struct sockaddr_in *addr, const char *ip, int port);
int  send_message(int file_descriptor, const char *message);
int  receive_message(int file_descriptor, char *buffer, int buffer_size);
void close_socket(int file_descriptor);

int  socket_server(void);
int  socket_client(void);

int  open_serial(const char *port, int baud);
int  read_serial(int fd, char *buffer, int size);
int  write_serial(int fd, const char *data);
void close_serial(int fd);

void serial_to_socket_bridge(const char *serial_port, int baud, int tcp_port);
void serial_to_udp_bridge(const char *serial_port, int baud, int udp_port);

#endif
