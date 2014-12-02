#include <pthread.h>

#include "../../Ex1/wrrd.h"
#include "monitor.h"


int main(void) {
    int i;
    pthread_t writers_ids[NB_WRITERS];
    long int return_values[NB_WRITERS];

    /**
     * Thread launch.
     */
    for (i = 0; i < NB_WRITERS; i++) {
        if (pthread_create(&writers_ids[i], NULL, &writer, NULL)) {
            perror("Error creating thread");
            exit(-1);
        }
    }

    /**
     * Signal handling.
     */
    while(1) {}

    /**
     * Join threads.
     */
    for (i = 0; i < NB_WRITERS; i++) {
        if (pthread_join(readers_ids[i], (void**) &return_values[i])) {
            perror("Error joining threads");
            exit(-1);
        }
        printf("Thread %d/%d returned %d\n", i + 1, NB_WRITERS, (int) return_values[i]);
    }

    exit(0);
}
