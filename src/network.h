#ifndef DLB_NETWORK_H
#define DLB_NETWORK_H

#include <netdb.h>
#include <pthread.h>
#include "error.h"


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
