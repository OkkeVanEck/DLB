#include "hardware.h"
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>


/* Get hardware info of local machine. */
struct hw_info* get_hw_info() {
    /* Get current number of CPUs available, RAM size, and RAM available. */
    int nprocs = get_nprocs();

    /* Set new values. */
    struct hw_info* hw_info = malloc(sizeof(struct hw_info));
    hw_info->nprocs = nprocs;

    return hw_info;
}


int main() {
    struct hw_info* hw_info = get_hw_info();
    printf("Nprocs: %d\n", hw_info->nprocs);
    free(hw_info);
    return 0;
}