#include "network.h"
//#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

/* Define constants for network traffic. */
#define BUFF_SIZE 80
#define SA struct sockaddr


/* Create and bind local socket for communication.
 * Uses the return values as specified in the header file.
 */
struct comms* create_socket() {
    int sockfd;
    struct sockaddr_in servaddr;

    /* Create new socket and nullify server address. */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed..\n");
        exit(NET_SOCKET_CREATION_FAILED);
    } else
        printf("Socket successfully created.\n");
    bzero(&servaddr, sizeof(servaddr));

    /* Assign IP and auto assign the port. */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = 0;

    /* Bind socket to IP. */
    if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed..\n");
        exit(NET_SOCKET_BINDING_FAILED);
    } else
        printf("Socket successfully binded.\n");

    /* Turn on listening for socket. */
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed..\n");
        exit(NET_SOCKET_LISTENING_FAILED);
    }
    else
        printf("Server listening.\n");

    /* Store all required info for communication and return. */
    struct comms* comm = malloc(sizeof (struct comms));
    comm->sockfd = sockfd;
    comm->servaddr = servaddr;

    return comm;
}

/* Listener function used by thread to connect to clients. */
void* listener(void* data) {
    struct comms* comm = data;
    struct sockaddr_in sockaddr_cli;
    int connfd;

    /* Block till a client connects to the socket. */
    connfd = accept(comm->sockfd, (SA*)&sockaddr_cli, (socklen_t*)sizeof (sockaddr_cli));
    if (connfd < 0) {
        printf("Server accept failed..\n");
        pthread_exit("NET_SERVER_ACCEPT_FAILED");
    }

    /* Process connected client. */
    printf("Server accepted a client.\n");
    // TODO: Process the connection file descriptor.

    return NULL;
}

/* Create server and start tread to listen for incoming clients. */
struct comms* create_server() {
    /* Create socket and bind an address. */
    struct comms* comm = create_socket();

    /* Create thread for listening to accept other clients. */
    pthread_t listener_thread;
    int retval = pthread_create(&listener_thread, NULL, listener, (void*)comm);
    if (retval < 0) {
        printf("Creating listener thread failed..\n");
        exit(NET_LISTENER_CREATION_FAILED);
    } else
        printf("Listening thread created.\n");

    return comm;
}

/* Close server by joining all threads and freeing allocated memory. */
void close_server(struct comms* comm) {
    /* Cancel the listener thread. */
    int retval = pthread_cancel(comm->listener_thread);
    if (retval < 0) {
        printf("Listener thread cancelation failed..\n");
        exit(NET_LISTENER_CANCELATION_FAILED);
    } else {
        printf("Listener thread canceled.\n");
    }

    /* Join the listener thread. */
    void* listener_retval;
    retval = pthread_join(comm->listener_thread, &listener_retval);
    if (retval < 0) {
        // TODO: Read listener_retval en compare to error code. Remove JOIN_FAILED code..
        printf("Listener thread join failed..\n");
        exit(NET_LISTENER_JOIN_FAILED);
    } else {
        printf("Listener thread joined.\n");
    }

    /* Close sockets. */
    close(comm->sockfd);

    /* Free allocated memory. */
    free(comm);
}
