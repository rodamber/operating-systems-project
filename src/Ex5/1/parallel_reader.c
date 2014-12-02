#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#include "../../Ex1/wrrd.h"
#include "reader.h"

int next_read_index  = 0;
int next_write_index = 0;


int main(void) {
    int  i;
    char filename[FNLEN + 1];
    pthread_t readers_ids[NB_READERS];
    long int return_values[NB_READERS];

    /**
     * Sincronization objects initialization.
     */
    if (pthread_mutex_init(&buffer_mutex, NULL)
                    || sem_init(&sem_info, 0, 0)
                    || sem_init(&sem_no_info, 0, BUFFER_SIZE)) {
        perror("Error creating sincronization objects");
        exit(-1);
    }

    /**
     * Thread launch.
     */
    for (i = 0; i < NB_READERS; i++) {
        if (pthread_create(&readers_ids[i], NULL, &reader, NULL)) {
            perror("Error creating thread");
            exit(-1);
        }
    }

    printf("Enter the file(s) name(s):\n");
    /**
     * Read filenames from input and pass them to child threads.
     */
    while (1) {
        sem_wait(&sem_no_info);

        if (read(0, filename, FNLEN + 1) < 0) { /* the "+ 1" is there to read a ' ' or a '\n' */
            perror("Error reading from stdin");
            exit(-1);
        }

        pthread_mutex_lock(&buffer_mutex);

        filename[FNLEN] = '\0';
        strcpy(buffer[next_write_index], filename);
        next_write_index = (next_write_index + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&sem_info);
    }

    /**
     * Join threads
     */
    for (i = 0; i < NB_READERS; i++) {
        if (pthread_join(readers_ids[i], (void**) &return_values[i])) {
            perror("Error joining threads");
            exit(-1);
        }
        printf("Thread %d/%d returned %d\n", i + 1, NB_READERS, (int) return_values[i]);
    }

    /**
     * Sincronization objects elimination.
     */
    if (pthread_mutex_destroy(&buffer_mutex)
                    || sem_destroy(&sem_info)
                    || sem_destroy(&sem_no_info)) {
        perror("Error destroying sincronization objects");
        exit(-1);
    }

    exit(0);
}
