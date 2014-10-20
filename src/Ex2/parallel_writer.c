#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NB_CHILDS 10


int main(void) {

    int i;
    int nb_forks = 0;		/* number of child processes created */
    int status = 0;
    time_t t = time(NULL);

    for(i = 0; i < NB_CHILDS; i++) {
	pid_t pID = fork();

	if (pID == 0) {
	    nb_forks++;
	    execl("wr", NULL);
	}
	else if (pID < 0) {
	    printf("Failed to fork!\n");
	}
    }

    for(i = 0; i < nb_forks; i++) {
	wait(&status);
    }

    printf("Time: %d\n", (int)(time(NULL) - t));

    return 0;
}
