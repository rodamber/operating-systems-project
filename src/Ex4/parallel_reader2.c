#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "../Ex1/wrrd.h"

#define NB_THREADS  3

void* reader(void* argv);

int main(void) {
    int i;
    char  n;
    pthread_t my_t[NB_THREADS];

    srand(time(NULL));

    for (i = 0; i < NB_THREADS; ++i) {
        n = '0' + rand() % FILENUM;
        /* FIXME: Alterar isto para enviar o nome do ficheiro como parametro em vez de o random. Alterar makefile (wrrdaux) */
        if (pthread_create(&my_t[i], NULL, &reader, (void*)&n)) {
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(errno));
            return -1;
        }
    }
    for (i = 0; i < NB_THREADS; ++i) {
        void* return_value = NULL;
            /* FIXME: Perguntar ao professor qual a diferença entre chamar return (void*) -1 e return -1 no que diz respeito ao valor return_value no pthread_join */
        if (pthread_join(my_t[i], &return_value)) {
            fprintf(stderr, "Error joining thread %d: %s\n", i, strerror(errno));
            return -1;
        }
        /* FIXME: SEG FAULT */
        printf("Thread %d finished and returned %d.\n", i, *(int*)return_value);
    }
    return 0;
}

void* reader(void* arg) {

    char filename[FNLEN + 1];
    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  fdesc;     /* file descriptor */
    int  strn;

    if (arg != NULL) {
        /* FIXME: SEG FAULT*/
        getfile(filename, *(char*)arg);
    }
    else {
        /*
         * Set a seed for use by rand() inside getfile().
         * See documentation in wrrd.h .
         */
        srand(time(NULL));
        getfile(filename, -1);
    }

    /*
     * Open file. Return if there was an error opening the file.
     *
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
        perror("Error opening file");
        return (void*) -1;
    }

    printf("Checking %s...\n", filename);

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
    if (strlen(firstline) != STRLEN || firstline[0] < 'a'
                                    || firstline[0] > 'j') {
        return (void*) -1;
    }
    for (i = 1; i < STRLEN - 1; i++) {
        if (firstline[i] != firstline[0]) {
            return (void*) -1;
        }
    }
    if (firstline[STRLEN - 1] != '\n') {
        return (void*) -1;
    }

    /*
     * Check if all lines are equal. Return if not.
     */
    for  (strn = 0; read(fdesc, line, STRLEN); strn++) {
        line[STRLEN] = '\0';

        if (strcmp(line, firstline)) {
            return (void*) -1;
        }
    }

    /*
     * Return if there aren't STRNUM valid strings in the file or if there
     * was an error reading the file.
     */
    if (strn != STRNUM - 1) { /* -1 because the first line was already read */
        return (void*) -1;
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

    printf("%s is correct.\n", filename);
    return (void*) -1;
    return 0;
}
