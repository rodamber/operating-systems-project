#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NB_CHILDS 10


int main(void) {

    int i;
    int nb_forks = 0;		/* stores number of child processes created */
    int status = 0;
    time_t start = time(NULL);

    printf("Creating child processes...\n");
    for(i = 0; i < NB_CHILDS; i++) {
	pid_t pID = fork();

	if (pID == 0) {
	    nb_forks++;
	    execl("../Ex1/wr", NULL);
            exit(0);
	    /* chamar exit ou nao chamar exit, eis a questao... */
	}
	else if (pID < 0) {
	    printf("Failed to fork!\n");
	}
    }

    printf("Waiting for childs to finish...\n");
    for(i = 0; i < NB_CHILDS; i++) {
	wait(&status);
	/* verificar o status? */
    }

    printf("Finished. Time: ~%ds\n", (int)(time(NULL) - start));
    /* a ideia e por isto a dar com precisao de milisegundos. nao tentem fazer cast para double ou float, nao vai funcionar */
    return 0;
}
