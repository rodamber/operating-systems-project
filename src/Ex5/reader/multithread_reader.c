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
    char c;
    char filename[FNLEN + 1] = {'\0'};
    pthread_t readers_ids[NB_READERS];
    long int return_values[NB_READERS];
    int return_value = 0;

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
    while (0 != strcmp(filename, "sair")) {
        ssize_t bytes_read;

        if (sem_wait(&sem_no_info)) {
            perror("Error on sem_wait (parent thread)");
            exit(-1);
        }
        bytes_read = read(STDIN_FILENO, filename, FNLEN + 1);
        if (bytes_read < 0) {
            perror("Error reading from stdin");
            exit(-1);
        }
        if (pthread_mutex_lock(&buffer_mutex)) {
            perror("Error on pthread_mutex_lock (parent thread)");
            exit(-1);
        }

        if ( (c = filename[]) == '\n' || c == ' ') {
            filename[bytes_read - 1] = '\0';
        }
        else {
            filename[bytes_read] = '\0';
        }
        strcpy(buffer[next_write_index], filename);
        next_write_index = (next_write_index + 1) % BUFFER_SIZE;

        if (pthread_mutex_unlock(&buffer_mutex)) {
            perror("Error on pthread_mutex_unlock (parent thread)");
            exit(-1);
        }
        if (sem_post(&sem_info)) {
            perror("Error on sem_post (parent thread)");
            exit(-1);
        }
    }

    /**
     * Join threads
     */
    for (i = 0; i < NB_READERS; i++) {
        int ret;
        if (pthread_join(readers_ids[i], (void**) &return_values[i])) {
            perror("Error joining threads");
            exit(-1);
        }
        ret = (int) return_values[i];
        printf("Thread %d/%d returned %d\n", i + 1, NB_READERS, ret);
        if (ret != 0) {
            return_value = -1;
        }
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
    printf("Returned %d\n", return_value);
    return return_value;
}
