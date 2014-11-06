#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NB_CHILDS 3

/* TODO: passar valor aleatorio ao execl */

int main(void) {

    int i;
    int nb_forks = 0;   /* stores number of childs processes created */
    int status = 0;

    printf("Creating child processes...\n");
    for(i = 0; i < NB_CHILDS; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            if (execl("../Ex1/rd", "rd", i, (char*) NULL) < 0) {
                perror("Error executing reader");
                exit(-1);
            }
            exit(0);
        }
        else if (pid < 0) {
            perror("Failed to fork process");
            exit(-1);
        }
        else {
            nb_forks++;
        }
    }

    printf("Waiting for childs to finish...\n");
    for (i = 0; i < nb_forks; i++) {
        while (wait(&status) == -1);
        printf("Child with pid=%ld completed with status 0x%x.\n", (long)pid, status);
    }

    return 0;
}
