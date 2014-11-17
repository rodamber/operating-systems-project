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

typedef struct {
    char file_index;
    int  start;
    int  end;
    int  return_value;
} thread_info;

void* reader(void* arg);

int main(void) {
    int i;
    char n  = '0' + rand() % FILENUM;
    int nb_lines = STRNUM / NB_THREADS;
    pthread_t my_t[NB_THREADS];
    thread_info reader_info_v[NB_THREADS];

    for (i = 0; i < NB_THREADS; ++i) {
        reader_info_v[i].return_value = -1;
    }
    srand(time(NULL));

    for (i = 0; i < NB_THREADS; ++i) {
        reader_info_v[i].file_index = n;
        reader_info_v[i].start      = i * nb_lines;


        if (i <  NB_THREADS - 1) {
            reader_info_v[i].end = (i + 1) * nb_lines;
        }
        else {
            reader_info_v[i].end = STRNUM;
        }

        if (pthread_create(&my_t[i], NULL, &reader, (void*) &reader_info_v[i])) {
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(errno));
            return -1;
        }
    }
    for (i = 0; i < NB_THREADS; ++i) {
        thread_info* ti = &reader_info_v[i];
        if (pthread_join(my_t[i], (void**) &ti)) {
            fprintf(stderr, "Error joining thread %d: %s\n", i, strerror(errno));
            return -1;
        }
        printf("Thread %d finished and returned %d.\n", i, ti->return_value);
    }
    return 0;
}

void* reader(void* arg) {

    char filename[FNLEN + 1];
    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  start = ((thread_info*) arg)->start;
    int  end   = ((thread_info*) arg)->end;
    int  fdesc;          /* file descriptor */
    int  strn;

    getfile(filename, ((thread_info*) arg)->file_index);

    /*
     * Open file. Return if there was an error opening the file.
     *
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
        perror("Error opening file");
        return arg;
    }

    printf("Checking %s...\n", filename);

    if (flock(fdesc, LOCK_SH) < 0) {
        perror("Error locking file");
        return arg;
    }

    /*
     * Read first line of the file. Return if there was an error reading the file.
     */
    if ((read(fdesc, firstline, STRLEN)) < 0) {
        perror("Error reading file");
        return arg;
    }

    firstline[STRLEN] = '\0';

    /*
     * First line must be composed of STRLEN - 1  equal chars between
     * 'a' and 'j', followed by a newline character, '\n'.
     */
    if (strlen(firstline) != STRLEN || firstline[0] < 'a'
                                    || firstline[0] > 'j') {
        return arg;
    }
    for (i = 1; i < STRLEN - 1; i++) {
        if (firstline[i] != firstline[0]) {
            return arg;
        }
    }
    if (firstline[STRLEN - 1] != '\n') {
        return arg;
    }

    /*
     * Move the pointer of the file descriptor.
     */
    if (lseek(fdesc, sizeof(char) * STRLEN * start, SEEK_SET) < 0) {
        perror("Error while forwarding file descriptor pointer");
        return arg;
    }

    /*
     * Check if all lines are equal (between start and end). Return if not.
     */
    for (strn = start; strn < end; strn++) {
        if (read(fdesc, line, STRLEN) < 0) {
            perror("Error while reading the file");
            return arg;
        }
        line[STRLEN] = '\0';
        if (strcmp(line, firstline)) {
            return arg;
        }
    }

    if (flock(fdesc, LOCK_UN) < 0) {
        perror("Error unlocking file");
        return arg;
    }

    /*
     * Return upon failure to close.
     */
    if (close(fdesc) < 0) {
        perror("Error closing file");
        return arg;
    }

    printf("%s is correct.\n", filename);
    ((thread_info*) arg)->return_value = 0;
    return arg;
}
