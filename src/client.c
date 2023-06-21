#include "client.h"
#include "network.h"

int main(void) {
    /* Create server with listening thread for other clients. */
    struct comms* comm = create_server();

    /* Close server. */
    close_server(comm);

    return 0;
}