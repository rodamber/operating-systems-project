/*perguntar ao professor se e preciso fazer verificacoes para inicializaçao (por exemplo, sem_init), e para utilizaçao (por exemplo, sem_wait, sem_post) dos objectos de sincronizaçao*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#include "../../../Ex1/wrrd.h"
#include "parallel_reader1.h"

#define NB_THREADS  50
#define FINISH      "sair"


int main(void) {
    int i;
    int  next_write_index = 0;
    char input;
    char filename[FNLEN + 1];
    sem_t sem_info;
    pthread_t readers_ids[NB_THREADS];

    /**
     * Sincronization objects initialization.
     */
    if (pthread_mutex_init(&buffer_mutex, NULL) || sem_init(&sem_info,0, 0) || sem_init(&sem_no_info, 0, BUFFER_SIZE)) {
        perror("Error creating sincronization objects");
        exit(-1);
    }

    /**
     * Thread launch.
     */
    for (i = 0; i < NB_THREADS; i++) {
        if (pthread_create(&readers_ids[i], NULL, &reader, NULL)) {
            perror("Error creating thread");
            exit(-1);
        }
    }

    /**
     * Read filenames from input. Finish when "sair" is read from input.
     */
    while (!strcmp(filename, FINISH)) {
        if (read(0, &input, 1) < 0) {
            perror("Error reading from stdin");
            exit(-1);
        }

        if (!strcmp(&input, ' ')) {
            continue;
        }

        strncat(filename, &input, 1);

        sem_wait(&sem_no_info);
        pthread_mutex_lock(&buffer_mutex);

        strcpy(buffer[next_write_index], filename);
        (next_write_index++) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&sem_no_info);

        filename[0] = '\0';
    }

    /**
     * Join threads
     */
    for (i = 0; i < NB_THREADS; i++) {
        int* return_value_ptr = NULL;
        if (pthread_join(readers_ids[i], (void**) &return_value_ptr)) {
            perror("Error joining threads");
            exit(-1);
        }
        printf("Thread %d/%d returned %d\n", i, NB_THREADS, *return_value_ptr);
    }

    /**
     * Sincronization objects elimination.
     */
    if (pthread_mutex_destroy(&buffer_mutex) || sem_destroy(&sem_info) || sem_destroy(&sem_no_info)) {
        perror("Error destroying sincronization objects");
        exit(-1);
    }

    exit(0);
}
