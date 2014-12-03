#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../Ex1/wrrd.h"
#include "writer.h"


static int file_locking  = 1;
static int error_writing = 0;
static int finish_flag   = 0;

/*
 * We want the previous flags to be read only for everything except for
 * the main function.
 */
int get_file_locking (void) { return file_locking;  }
int get_error_writing(void) { return error_writing; }
int get_finish_flag  (void) { return finish_flag;   }

void sigusr1_handler(int sig) { (void)sig; file_locking  = !file_locking;  }
void sigusr2_handler(int sig) { (void)sig; error_writing = !error_writing; }
void sigtstp_handler(int sig) { (void)sig; finish_flag   = 1;              }


int main(void) {
    int i;
    pthread_t writers_ids[NB_WRITERS];
    long int return_values[NB_WRITERS];
	int return_value = -1;

    struct sigaction sigusr1;
    struct sigaction sigusr2;
    struct sigaction sigtstp;

    /*
     * Initialize sigaction handlers.
     */
    sigusr1.sa_handler = sigusr1_handler;
    sigusr2.sa_handler = sigusr2_handler;
    sigtstp.sa_handler = sigtstp_handler;

    /*
     * Initialize signal sets to be empty.
     */
    sigemptyset(&sigusr1.sa_mask);
    sigemptyset(&sigusr2.sa_mask);
    sigemptyset(&sigtstp.sa_mask);

    /*
     * Add the specified signals to the signal sets.
     */
    sigaddset(&sigusr1.sa_mask, SIGUSR1);
    sigaddset(&sigusr2.sa_mask, SIGUSR2);
    sigaddset(&sigtstp.sa_mask, SIGTSTP);

    /*
     * Reset sigaction flags.
     */
    sigusr1.sa_flags = 0;
    sigusr2.sa_flags = 0;
    sigtstp.sa_flags = 0;

    /*
     * Assigns actions to the signals.
     */
    sigaction(SIGUSR1, &sigusr1, NULL);
    sigaction(SIGUSR2, &sigusr2, NULL);
    sigaction(SIGTSTP, &sigtstp, NULL);

    /*
     * Thread launch.
     */
    for (i = 0; i < NB_WRITERS; i++) {
        if (pthread_create(&writers_ids[i], NULL, &writer, NULL)) {
            perror("Error creating thread");
            exit(-1);
        }
    }

    /*
     * Join threads.
     */
    for (i = 0; i < NB_WRITERS; i++) {
		int ret;
        if (pthread_join(writers_ids[i], (void**) &return_values[i])) {
            perror("Error joining threads");
            exit(-1);
        }
		ret = (int) return_values[i];
        printf("Thread %d/%d returned %d\n", i + 1, NB_WRITERS, ret);
		if (ret == 0) {
			return_value = 0;
		}
    }
    return return_value;
}
