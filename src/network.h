#ifndef DLB_NETWORK_H
#define DLB_NETWORK_H

#include <netdb.h>
#include <pthread.h>


/* Define network exit errors. */
#define NET_SOCKET_CREATION_FAILED -1
#define NET_SOCKET_BINDING_FAILED -2
#define NET_SOCKET_LISTENING_FAILED -3
#define NET_SERVER_ACCEPT_FAILED -4
#define NET_LISTENER_CREATION_FAILED -5
#define NET_LISTENER_CANCELATION_FAILED -6
#define NET_LISTENER_JOIN_FAILED -7

/* Struct for managing communication. */
struct comms {
    int sockfd;
    struct sockaddr_in servaddr;
    pthread_t listener_thread;
};

/* Create server and start tread to listen for incoming clients. */
struct comms* create_server();

/* Close server by joining all threads and freeing allocated memory. */
void close_server(struct comms* comm);

#endif // DLB_NETWORK_H
