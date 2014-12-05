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

#include "../../Ex1/wrrd.h"
#include "reader.h"

static int finish_flag = 0;


void incorrect_file_msg(const char* filename, const char* msg) {
    printf("Incorrect file -> %s: %s\n", filename, msg);
}

void* reader(void* arg) {
    char filename[FNLEN + 1];
    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  incorrect_file = 0;
    int  fdesc;
    int  strn;

    (void) arg;

while (!finish_flag) {
    if (sem_wait(&sem_info)) {
        perror("Error on sem_wait (child thread)");
        exit(-1);
    }
    if (pthread_mutex_lock(&buffer_mutex)) {
        perror("Error on pthread_mutex_lock (child thread)");
        exit(-1);
    }
    if (0 != strcmp(buffer[next_read_index], "sair")) {
        strcpy(filename, buffer[next_read_index]);
        next_read_index = (next_read_index + 1) % BUFFER_SIZE;
    }
    else {
        finish_flag = 1;
        if (sem_post(&sem_info)) {
            perror("Error on sem_post (child thread)");
            exit(-1);
        }
    }
    if (pthread_mutex_unlock(&buffer_mutex)) {
        perror("Error on pthread_mutex_unlock (child thread)");
        exit(-1);
    }
    if (sem_post(&sem_no_info)) {
        perror("Error on sem_post (child thread)");
        exit(-1);
    }
    if (finish_flag) {
        break;
    }

    printf("Checking %s\n", filename);

    /*
     * Open file. Return if there was an error opening the file.
     *
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
        if (errno == ENOENT) {
            printf("File does not exist: %s\n", filename);
            continue;
        }
        perror("Error opening file");
        return (void*) -1;
    }
    if (flock(fdesc, LOCK_SH) < 0) {
        perror("Error locking file");
        return (void*) -1;
    }

    /*
     * Read file. Return if there was an error reading the file.
     */
    if ((read(fdesc, firstline, STRLEN)) < 0) {
        perror("Error reading file");
        return (void*) -1;
    }
    firstline[STRLEN] = '\0';

    /*
     * First line must be composed of STRLEN - 1  equal chars between
     * 'a' and 'j', followed by a newline character, '\n'.
     */
    if (strlen(firstline) != STRLEN || firstline[0] < 'a' || firstline[0] > 'j') {
        incorrect_file = 1;
        incorrect_file_msg(filename, "char not between 'a' and 'j'");
    }
    for (i = 1; i < STRLEN - 1; i++) {
        if (firstline[i] != firstline[0]) {
            incorrect_file = 1;
            incorrect_file_msg(filename, "line not all equal");
        }
    }
    if (firstline[STRLEN - 1] != '\n') {
        incorrect_file = 1;
        incorrect_file_msg(filename, "last char of line not a '\n'");
    }

    /*
     * Check if all lines are equal. Return if not.
     */
    for  (strn = 0; (i = read(fdesc, line, STRLEN)); strn++) {
        if (i == -1) {
            perror("Error reading file");
            return (void*) -1;
        }
        line[STRLEN] = '\0';

        if (strcmp(line, firstline)) {
            incorrect_file = 1;
            incorrect_file_msg(filename, "lines not all equal");
            break;
        }
    }

    /*
     * Return if there aren't STRNUM valid strings in the file.
     */
    if (strn != STRNUM - 1) { /* -1 because the first line was already read */
        incorrect_file = 1;
        incorrect_file_msg(filename, "illegal number of lines");
    }

    if (flock(fdesc, LOCK_UN) < 0) {
        perror("Error unlocking file");
        return (void*) -1;
    }

    /*
     * Return upon failure to close.
     */
    if (close(fdesc) < 0) {
        perror("Error closing file");
        return (void*) -1;
    }

    if (incorrect_file) {
        continue;
    }
    printf("%s is correct\n", filename);

} /* while(!finish_flag) */
    return (void*) 0;
}
