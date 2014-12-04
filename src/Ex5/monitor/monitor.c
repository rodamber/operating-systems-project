#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../Ex1/wrrd.h"

#define NB_CHILDS 2


int main(void) {
    char  input[FNLEN + 1];
    int   nb_childs;
    int   pipefd[2];
    int   return_value;
    pid_t reader_pid;
    pid_t writer_pid;

    /*
     * Create pipe for use between this process and the reader process.
     */
    if (pipe(pipefd) == -1) {
        perror("Could not create a pipe to reader");
        exit(-1);
    }

    printf("Creating child processes...\n");

    /*
     * Fork into writer.
     */
    writer_pid = fork();
    if (writer_pid == -1) {
        perror("Could not fork a child (parent->writer)");
        exit(-1);
    }
    if (writer_pid == 0) {
        if (execl("mt_wr", "mt_wr", NULL, (char*) NULL) == -1) {
            perror("Could not execute writer");
            exit(-1);
        }
    }

    /*
     * Fork into reader.
     */
    reader_pid = fork();
    if (reader_pid == -1) {
        perror("Could not fork a child (parent->reader)");
        exit(-1);
    }
    if (reader_pid == 0) {
        if (close(pipefd[1]) == -1) {
            perror("Could not close write end of pipe (reader)");
            exit(-1);
        }
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("Could not redirect stdin to reader");
            exit(-1);
        }
        if (execl("mt_rd", "mt_rd", NULL, (char*) NULL) == -1) {
            perror("Could not execute reader");
            exit(-1);
        }
    }

    if (close(pipefd[0]) == -1) {
            perror("Could not close read end of pipe (parent)");
            exit(-1);
    }

    while (1) {
        ssize_t bytes_read;

        bytes_read = read(STDIN_FILENO, input, FNLEN + 1);
        if (bytes_read == -1) {
            perror("Could not read from stdin");
            exit(-1);
        }
        input[bytes_read - 1] = '\0';

        if (strcmp(input, "il") == 0) {
            if (kill(writer_pid, SIGUSR1) == -1) {
                perror("Could not send SIGUSR1 to writer");
                exit(-1);
            }
        }
        else if (strcmp(input, "ie") == 0) {
            if (kill(writer_pid, SIGUSR2) == -1) {
                perror("Could not send SIGUSR2 to writer");
                exit(-1);
            }
        }
        else {
            int input_len = strlen(input);

            if (write(pipefd[1], input, input_len) != input_len) {
                perror("Could not write to reader");
                exit(-1);
            }
            if (strcmp(input, "sair") == 0) {
                if (close(pipefd[1]) == -1) {
                    perror("Could not close pipe to reader");
                    exit(-1);
                }
                if (kill(writer_pid, SIGTSTP) == -1) {
                    perror("Could not send SIGTSTP to writer");
                    exit(-1);
                }
                break;
            }
        }
    }

    /*
     * Wait for child processes.
     */
    for (nb_childs = 0; nb_childs < NB_CHILDS; nb_childs++) {
        int ret;
        int status;

        while (wait(&status) == -1)
            ;
        if (WIFEXITED(status) != 0) {
            ret = WEXITSTATUS(status);
            printf("Child finished and returned %d\n", ret);
        }
        if (ret != 0) {
            return_value = -1;
        }
    }
    return return_value;
}
