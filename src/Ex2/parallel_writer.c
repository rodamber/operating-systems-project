#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NB_CHILDS 10


int main(void) {

    int i;
    int nb_forks = 0;        /* stores number of child processes created */
    int status = 0;

    struct timeval tvstart;    /* beggining date */
    struct timeval tvend;    /* ending date */
    struct timeval tvduration;    /* date difference */
    double duration; /* date difference in microsseconds */

    if (gettimeofday(&tvstart, NULL)) {
        return -1;
    }

    printf("Creating child processes...\n");
    for(i = 0; i < NB_CHILDS; i++) {
        pid_t pID = fork();

        if (pID == 0) {
            if (execl("../Ex1/wr", "wr", (char*) NULL) < 0) {
                return -1;
            }
            exit(0);
        }
        else if (pID < 0) {
            printf("Failed to fork!\n");
        }
        else {
            nb_forks++;
        }
    }

    printf("Waiting for childs to finish...\n");
    for(i = 0; i < nb_forks; i++) {
    wait(&status);
    }

    gettimeofday(&tvend, NULL);

    /* calculate and print date difference */
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("Finished.\nDuration: %.3fs\n", duration / 1000000);

    return 0;
}
