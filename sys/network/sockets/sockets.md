# Notes

USES -> 
socket({address family}, {sockey type}, {option level}) // for address family on layer get layerstream
setsockopt({socket}, {layer option}, {specific option}, &value, sizeof(value))



Configs: 
Address families:
- AF_INET -> IPv4 address family
- AF_INET6 -> IPv6 address family
- AF_UNIX (AF_LOCAL) -> local domain socket
- AF_PACKET -> Raw packets with direct access to network internet hardware.
- AF_NETLINK -> Com between userspace and kernelspace.
- AF_BLUETOOTH -> Bluetooth socket for wireless device com.
- AF_VSOCK -> Virtual sockets between vm and host.

Socket stream:
- SOCK_STREAM -> states TCP => Ordered, reliable, two way handshake 
- SOCK_DGRAM -> states UDP => message based
- SOCK_RAW -> Raw packages
- SOCK_RDM -> Reliable datagram message => Ordered, reliable / message based
- SOCK_SEQPACKET -> Maintains message boundaries => guaranties delivery and ordering.
- extra options: | SOCK_NONBLOCK || SOCK_CLOEXEC

Network layer options:
_None in application layer
_Transport layer
- IPPROTO_TCP
- IPPROTO_UDP
- IPPROTO_SCTP
- IPPROTO_DCCP
_Network layer
- IPPROTO_IP
- IPPROTO_IPV6
- IPPROTO_ICMP
- IPPROTO_IGMP
_Socket/OS abstraction layer
- SOL_SOCKET
- SOL_RAW
- SOL_PACKET
_Special Layers
- SOL_NETLINK
- SOL_BLUETOOTH
- SOL_ALG

Specific options
_IPPROTO_TCP
- TCP_NODELAY -> Disables Nagle's algorithm. Sends data immediately instead of waiting to accumulate more data. Reduces latency for interactive applications.
- TCP_KEEPIDLE -> Time (in seconds) before TCP starts sending keep-alive probes on idle connections. 
- TCP_KEEPINTVL -> Interval (in seconds) between keep-alive probes.
- TCP_KEEPCNT -> Number of keep-alive probes before giving up and closing the connection.
- TCP_MAXSEG -> Maximum segment size (MSS) for the connection. Usually set automatically, but you can override it.
- TCP_CORK -> Buffers data and only sends when buffer is full or socket is closed. Reduces number of packets sent (opposite of TCP_NODELAY).

_IPPROTO_UDP
- UDP_CORK -> Buffers UDP packets and only sends when buffer is full or socket is closed. Reduces number of packets sent.
- UDP_ENCAP -> Encapsulates UDP packets (for VPN/tunneling). Rarely used in typical applications.

_IPPROTO_SCTP       Default     Description
- SCTP_NODELAY ->   [0]         -> Sends data immediately instead of buffering. Reduces latency for interactive applications.
- SCTP_RTOMIN ->    [300](ms)   -> Minimum retransmission timeout in milliseconds. Controls earliest point to retry failed transmissions.
- SCTP_RTOMAX ->    [60000](ms) -> Maximum retransmission timeout in milliseconds. Prevents excessively long waits between retries.
- SCTP_RTOINIT ->   [3000](ms)  -> Initial retransmission timeout in milliseconds. Sets starting point for timeout calculations.
- SCTP_ASSOCINFO -> [sasoc_asocmaxrxt]: 10 retransmissions
                    [sasoc_cookie_life]: 60000 ms
                    -> Association-level parameters including max retransmissions and default send parameters.
- SCTP_INITMSG ->   [sinit_num_ostreams]: 10 streams
                    [sinit_max_instreams]: 65535 streams
                    [sinit_max_attempts]: 4 retries
                    [sinit_max_init_timeo]: 60000 ms
                    -> Initial message parameters for new associations, including number of streams and max attempts.
- SCTP_PRIMARY_ADDR ->  [defaults first] -> Sets the primary address for multi-homed associations. Used when endpoint has multiple network interfaces.
- SCTP_ADAPTATION_LAYER -> [0] -> Sets adaptation layer indication value for peer communication during handshake.
- SCTP_DISABLE_FRAGMENTS -> [0] -> Disables automatic message fragmentation. Messages larger than MTU will fail if enabled.
- SCTP_EVENTS ->            [sctp_event_subscribe] struct? -> Configures which SCTP events (data arrival, association changes, etc.) the socket receives as notifications.
- SCTP_AUTOCLOSE ->         [0] -> Automatically closes association after specified seconds of inactivity. Prevents zombie connections.
- SCTP_MAX_BURST ->         [4]packets -> Maximum number of packets to send in a single burst. Prevents overwhelming the network.
- SCTP_PARTIAL_DELIVERY_POINT -> [0] -> Threshold size in bytes for delivering partial messages to the application before complete message arrives.
- SCTP_CONTEXT ->                [0] -> User-defined context value attached to the socket for use in notifications and callbacks.
- SCTP_FRAGMENT_INTERLEAVE ->    [0] -> Controls whether fragmented messages from different streams can be interleaved during delivery.
- SCTP_AUTH_CHUNK ->        [disabled] struct -> Enables authentication (HMAC) for specific message chunk types for security.
- SCTP_HMAC_IDENT ->        [SHA-1] -> Specifies which HMAC algorithm (SHA-1, etc.) to use for message authentication.
- SCTP_AUTH_KEY ->          [not set] -> Sets an authentication key for securing messages between peers
- SCTP_AUTH_ACTIVE_KEY ->   [none] -> Activates a previously configured authentication key for use in current communications.
- SCTP_AUTH_DELETE_KEY ->   operation -> Removes a configured authentication key from the socket.
- SCTP_PEER_AUTH_CHUNKS ->  [read-only] -> Queries which message chunk types the peer has requested authentication for (read-only).
- SCTP_LOCAL_AUTH_CHUNKS -> [read-only] -> Queries which message chunk types this socket requires authentication for (read-only).
- SCTP_GET_ASSOC_NUMBER ->  [read-only] -> Gets the total number of active associations on this socket (read-only).
- SCTP_STATUS ->            [read-only] -> Retrieves detailed status information about an association including state, addresses, and RTT.
- SCTP_GET_PEER_ADDRS ->    [read-only] -> Retrieves the list of all addresses known for the peer in an association (read-only).
- SCTP_SOCKOPT_BINDX_ADD -> operation -> Adds additional local addresses to bind to for multi-homing support.
- SCTP_SOCKOPT_BINDX_REM -> operation -> Removes previously bound local addresses from multi-homing configuration.
- SCTP_CONNECTX ->          operation -> Establishes association with multiple peer addresses simultaneously for redundancy.
- SCTP_SEND_FAILED ->       [read-only] -> Notification event when a message fails to send to the peer.
- SCTP_ADDR_CONFIRMED ->    [read-only] -> Notification event when a peer address is confirmed as reachable.

_IPPROTO_DCCP -> not really used in practice / can be good for low latency streaming.
-    DCCP_SOCKOPT_PACKET_SIZE
- DCCP_SOCKOPT_SERVICE
- DCCP_SOCKOPT_CHANGE_L/CHANGE_R 
- DCCP_SOCKOPT_GET_CUR_MPS
- DCCP_SOCKOPT_SERVER_TIMEWAIT
- DCCP_SOCKOPT_SEND_CSCOV/RECV_CSCOV
- DCCP_SOCKOPT_QPOLICY_ID/QPOLICY_TXQLEN

_IPPROTO_IP
- IP_TOS -> Sets QoS priority/traffic class for packets. Tells routers how to prioritize (real-time, bulk data, interactive, etc.).
- IP_TTL -> Sets hop limit (0-255). Controls how many network hops a packet can traverse before being discarded.
- IP_MULTICAST_TTL -> Sets TTL specifically for multicast packets. Usually lower than unicast TTL.
- IP_MULTICAST_IF -> Specifies which network interface to use for sending multicast packets.
- IP_ADD_MEMBERSHIP -> Joins a multicast group on a specified interface.
- IP_DROP_MEMBERSHIP -> Leaves a previously joined multicast group.
- IP_MULTICAST_LOOP -> Controls whether multicast packets sent by this socket are looped back to the sender.
- IP_RECVTOS -> Enables receiving the TOS value from incoming packets (read-only reception).
- IP_PKTINFO -> Enables receiving packet information (source address, destination address, interface) with incoming packets. 
- IP_RECVTTL -> Enables receiving the TTL value from incoming packets.
...

_IPPROTO_IPV6
...
_IPPROTO_ICMP
...
_IPPROTO_IGMP

...

_SOL_SOCKET
- SO_REUSEADDR -> Allows binding to an address in TIME_WAIT state. Lets you restart a server quickly without waiting for port release.
- SO_REUSEPORT -> Allows multiple sockets to bind to the same address and port. Enables load balancing across processes.
- SO_KEEPALIVE -> Enables keep-alive probes on TCP connections. Detects and closes dead connections automatically.
- SO_LINGER -> Controls how close() behaves. Can wait for pending data, close immediately, or linger for a time.
- SO_RCVBUF -> Sets the size of the receive buffer. Larger buffers improve performance for high-bandwidth connections.
- SO_SNDBUF -> Sets the size of the send buffer. Controls how much data can be queued before sending.
- SO_RCVTIMEO -> Sets timeout for receive operations. Prevents recv() from blocking indefinitely.
- SO_SNDTIMEO -> Sets timeout for send operations. Prevents send() from blocking indefinitely.
- SO_BROADCAST -> Allows sending broadcast messages on UDP sockets. Enables sending to entire networks.
- SO_DONTROUTE -> Bypasses normal routing. Sends packets directly to the specified interface without routing lookup.
- SO_OOBINLINE -> Receives out-of-band (urgent) data inline with regular data on TCP sockets.
- SO_TYPE -> Returns the socket type (SOCK_STREAM, SOCK_DGRAM, etc.). Read-only.
- SO_ERROR -> Returns pending socket errors. Read-only. Used to check for async errors.
- SO_ACCEPTFILTER -> Installs a filter for incoming connections (BSD/macOS). Filters which connections are accepted.
- SO_BINDTODEVICE -> Binds socket to a specific network interface. Restricts socket to one interface only.
- SO_BINDTOIFINDEX -> Binds socket to a specific interface by index number (Linux).
- SO_DOMAIN -> Returns the address family (AF_INET, AF_INET6, etc.). Read-only.
- SO_PROTOCOL -> Returns the protocol number. Read-only. 
- SO_MARK -> Sets a mark/label on packets for netfilter/iptables rules (Linux).
- SO_PRIORITY -> Sets priority for outgoing packets. Affects packet scheduling.
- SO_PASSCRED -> Enables receiving peer credentials (UID, GID, PID) on Unix domain sockets.
- SO_PEERCRED -> Gets peer credentials for connected sockets. Read-only.
- SO_PEERSEC -> Gets SELinux security context of peer (Linux).
- SO_TIMESTAMP -> Enables receiving kernel timestamp with each packet.
- SO_TIMESTAMPNS -> Enables receiving kernel timestamp with nanosecond precision.
- SO_TIMESTAMPING -> Advanced timestamping with multiple options for hardware/software timestamps.
- SO_DEBUG -> Enables debug mode. Tells kernel to record debug info for the socket.
- SO_NOSIGPIPE -> Prevents SIGPIPE signal when writing to closed socket (macOS/BSD).
- SO_NREAD -> Returns number of bytes available to read. Read-only.
- SO_NWRITE -> Returns number of bytes available to write. Read-only.
- SO_MAX_PACING_RATE -> Sets maximum packet pacing rate in bytes per second (Linux).
- SO_INCOMING_CPU -> Gets CPU that processed the last packet. Read-only.
- SO_ATTACH_FILTER/SO_DETACH_FILTER -> Attaches/detaches Berkeley Packet Filter (BPF) for packet filtering.
- SO_ATTACH_BPF/SO_DETACH_BPF -> Modern equivalent for attaching eBPF programs.
- SO_LOCK_FILTER -> Locks the attached filter (prevents removal).
- SO_BPF_EXTENTIONS -> Returns available BPF extensions. Read-only.



Application 
socket_option tcp_server_opts[] = {
    {SOL_SOCKET, SO_REUSEADDR, 1},
    {SOL_SOCKET, SO_RCVBUF, 65536},
    {0, 0, 0}  // Terminator
}

iterate
void apply_socket_options(int sock, socket_option *opts) {
    for (int i = 0; opts[i].level != 0; i++) {
        setsockopt(sock, opts[i].level, opts[i].optname,
                   &opts[i].value, sizeof(opts[i].value));
    }
}

TCP over IPv4 (AF_INET, SOCK_STREAM)      → ~45-50%
TCP over IPv6 (AF_INET6, SOCK_STREAM)     → ~15-20%
UDP over IPv4 (AF_INET, SOCK_DGRAM)       → ~10-15%
UDP over IPv6 (AF_INET6, SOCK_DGRAM)      → ~5-10%
Unix Domain Sockets (AF_UNIX, SOCK_STREAM)→ ~10-15%
Raw Sockets (AF_PACKET, SOCK_RAW)         → ~2-5%
Other combinations                         → ~5%

c// Web server (typical)
socket(AF_INET, SOCK_STREAM, 0);  ✓ Common
socket(AF_INET6, SOCK_STREAM, 0); ✓ Increasingly common

// DNS client
socket(AF_INET, SOCK_DGRAM, 0);   ✓ Standard

// Microservices (Docker)
socket(AF_UNIX, SOCK_STREAM, 0);  ✓ Very common now

// Video streaming
socket(AF_INET, SOCK_DGRAM, 0);   ✓ Common

// Network packet capture
socket(AF_PACKET, SOCK_RAW, IPPROTO_IP); ✓ Specialized tools




//////




