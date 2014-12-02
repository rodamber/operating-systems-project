#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../../../Ex1/wrrd.h"
#include "monitor.h"

void* reader(void* arg) {

    char filename[FNLEN + 1];
    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  fdesc;     /* file descriptor */
    int  strn;

while(1) {
    sem_wait(&sem_info);
    pthread_mutex_lock(&buffer_mutex);

    strcpy(filename, buffer[next_read_index]);
    next_read_index = (next_read_index + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&buffer_mutex);
    sem_post(&sem_no_info);

    filename[FNLEN] = '\0';

    printf("Checking %s\n", filename);

    /*
     * Open file. Return if there was an error opening the file.
     *
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
        perror("Error opening file");
        exit(-1);
    }

    if (flock(fdesc, LOCK_SH) < 0) {
        perror("Error locking file");
        exit(-1);
    }

    /*
     * Read file. Return if there was an error reading the file.
     */
    if ((read(fdesc, firstline, STRLEN)) < 0) {
        perror("Error reading file");
        exit(-1);
    }

    firstline[STRLEN] = '\0';

    /*
     * First line must be composed of STRLEN - 1  equal chars between
     * 'a' and 'j', followed by a newline character, '\n'.
     */
    if (strlen(firstline) != STRLEN || firstline[0] < 'a' || firstline[0] > 'j') {
        exit(-1);
    }
    for (i = 1; i < STRLEN - 1; i++) {
        if (firstline[i] != firstline[0]) {
            exit(-1);
        }
    }
    if (firstline[STRLEN - 1] != '\n') {
        exit(-1);
    }

    /*
     * Check if all lines are equal. Return if not.
     */
    for  (strn = 0; read(fdesc, line, STRLEN); strn++) {
        line[STRLEN] = '\0';

        if (strcmp(line, firstline)) {
            exit(-1);
        }
    }

    /*
     * Return if there aren't STRNUM valid strings in the file or if there
     * was an error reading the file.
     */
    if (strn != STRNUM - 1) { /* -1 because the first line was already read */
        exit(-1);
    }

    if (flock(fdesc, LOCK_UN) < 0) {
        perror("Error unlocking file");
        exit(-1);
    }

    /*
     * Return upon failure to close.
     */
    if (close(fdesc) < 0) {
        perror("Error closing file");
        exit(-1);
    }

    printf("%s is correct\n", filename);

} /* while(strcmp(...) != 0) */
}
