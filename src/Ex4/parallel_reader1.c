#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "../Ex1/wrrd.h"

#define NB_CHILDS 3


int main(void) {

    int i;
    int nb_forks = 0;   /* stores number of childs processes created */
    int status = 0;
    int return_value = -1;
    char arg;

    srand(time(NULL));

    printf("Creating child processes...\n");
    for(i = 0; i < NB_CHILDS; i++) {
        pid_t pid = fork();
        arg = '0' + rand() % FILENUM;

        if (pid == 0) {
            if (execl("../Ex1/rd", "rd", &arg, (char*) NULL) < 0) {
                perror("Error executing rd");
                exit(-1);
            }
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
        if (WIFEXITED(status)) {
            return_value = WEXITSTATUS(status);
            printf("Child finished and returned %d.\n", return_value);
        }
    }
    return 0;
}
