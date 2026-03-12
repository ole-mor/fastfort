#ifndef SOCKET_CONFIG_H
#define SOCKET_CONFIG_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

typedef struct {
    int level;
    int optname;
    int value;
} socket_option;

/* ----- TCP Profiles ----- */

socket_option tcp_interactive[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 65536},
    {SOL_SOCKET, SO_SNDBUF, 65536},
    {IPPROTO_TCP, TCP_NODELAY, 1},
    {SOL_SOCKET, SO_KEEPALIVE, 1},
    {IPPROTO_TCP, TCP_KEEPIDLE, 60},
    {IPPROTO_TCP, TCP_KEEPINTVL, 10},
    {IPPROTO_TCP, TCP_KEEPCNT, 5},
    {IPPROTO_IP, IP_TOS, IPTOS_LOWDELAY},
    {0, 0, 0}
};

socket_option tcp_bulk_transfer[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 1048576},
    {SOL_SOCKET, SO_SNDBUF, 1048576},
    {IPPROTO_TCP, TCP_NODELAY, 0},
    {SOL_SOCKET, SO_KEEPALIVE, 1},
    {IPPROTO_IP, IP_TOS, IPTOS_THROUGHPUT},
    {0, 0, 0}
};

socket_option tcp_connection_heavy[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_REUSEPORT, 1},
    {SOL_SOCKET, SO_RCVBUF, 32768},
    {SOL_SOCKET, SO_SNDBUF, 32768},
    {IPPROTO_TCP, TCP_NODELAY, 1},
    {IPPROTO_TCP, TCP_KEEPIDLE, 30},
    {IPPROTO_TCP, TCP_KEEPINTVL, 5},
    {IPPROTO_TCP, TCP_KEEPCNT, 3},
    {0, 0, 0}
};

socket_option tcp_client[] = {
    {SOL_SOCKET, SO_SNDTIMEO, 5000},
    {SOL_SOCKET, SO_RCVTIMEO, 5000},
    {IPPROTO_TCP, TCP_NODELAY, 1},
    {0, 0, 0}
};

/* ----- UDP Profiles ----- */

socket_option udp_high_throughput[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 262144},
    {SOL_SOCKET, SO_SNDBUF, 262144},
    {IPPROTO_IP, IP_TOS, IPTOS_THROUGHPUT},
    {SOL_SOCKET, SO_RCVTIMEO, 3000},
    {0, 0, 0}
};

socket_option udp_low_latency[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 65536},
    {SOL_SOCKET, SO_SNDBUF, 65536},
    {IPPROTO_IP, IP_TOS, IPTOS_LOWDELAY},
    {IPPROTO_IP, IP_MULTICAST_TTL, 32},
    {SOL_SOCKET, SO_RCVTIMEO, 1000},
    {0, 0, 0}
};

socket_option udp_multicast[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 131072},
    {SOL_SOCKET, SO_SNDBUF, 131072},
    {IPPROTO_IP, IP_MULTICAST_TTL, 32},
    {IPPROTO_IP, IP_MULTICAST_LOOP, 1},
    {0, 0, 0}
};

socket_option udp_client[] = {
    {SOL_SOCKET, SO_SNDTIMEO, 3000},
    {SOL_SOCKET, SO_RCVTIMEO, 3000},
    {SOL_SOCKET, SO_RCVBUF, 65536},
    {0, 0, 0}
};

/* ----- Security & Specialized Profiles ----- */

socket_option secure_socket[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVTIMEO, 5000},
    {SOL_SOCKET, SO_SNDTIMEO, 5000},
    {SOL_SOCKET, SO_KEEPALIVE, 1},
    {IPPROTO_TCP, TCP_NODELAY, 1},
    {IPPROTO_IP, IP_TTL, 64},
    {0, 0, 0}
};

socket_option raw_packet_filter[] = {
    {SOL_SOCKET, SO_RCVBUF, 262144},
    {IPPROTO_IP, IP_RECVTTL, 1},
    {IPPROTO_IP, IP_RECVTOS, 1},
    {IPPROTO_IP, IP_PKTINFO, 1},
    {0, 0, 0}
};

#endif
