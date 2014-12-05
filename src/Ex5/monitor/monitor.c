#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../Ex1/wrrd.h"
#include "../util/ex5_util.h"

#define READ_END  0
#define WRITE_END 1

#define NB_CHILDS 2


void lock_trigger_msg(void) {
    static int locks = 1;

    locks = !locks;
    if (locks) {
        puts("Using locks...");
    }
    else {
        puts("Not using locks...");
    }
}

void mistakes_trigger_msg(void) {
    static int mistakes = 0;

    mistakes = !mistakes;
    if (mistakes) {
        puts("Writing mistakes...");
    }
    else {
        puts ("No mistakes...");
    }
}

int main(void) {
    char input[FNLEN + 1] = {'\0'};

    int  i;
    int  pipefd[2];
    int  return_value;

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
    else if (writer_pid == 0) { /* child - writer */
        if (execl("../writer/mt_wr", "mt_wr", NULL, (char*) NULL) == -1) {
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
    else if (reader_pid == 0) { /* child - reader */
        if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
            perror("Could not redirect stdin to reader");
            exit(-1);
        }
        if (close(pipefd[WRITE_END]) == -1) {
            perror("Could not close write end of pipe (reader)");
            exit(-1);
        }
        if (execl("../reader/mt_rd", "mt_rd", NULL, (char*) NULL) == -1) {
            perror("Could not execute reader");
            exit(-1);
        }
    }

    if (close(pipefd[READ_END]) == -1) {
        perror("Could not close read end of pipe (parent)");
        exit(-1);
    }

    while (strcmp(input, "sair") != 0) {
        int input_length;

        if ((input_length = read_word(input, FNLEN + 1))  == -1) {
            perror("Could not read from stdin");
            exit(-1);
        }
        if (strcmp(input, "il") == 0) {
            lock_trigger_msg();
            if (kill(writer_pid, SIGUSR1) == -1) {
                perror("Could not send SIGUSR1 to writer");
                exit(-1);
            }
        }
        else if (strcmp(input, "ie") == 0) {
            mistakes_trigger_msg();
            if (kill(writer_pid, SIGUSR2) == -1) {
                perror("Could not send SIGUSR2 to writer");
                exit(-1);
            }
        }
        else {
            input[input_length] = '\0';
            if (write(pipefd[WRITE_END], input, input_length + 1) != (input_length + 1)) {
                perror("Could not write to reader");
                exit(-1);
            }
        }
    }

    if (close(pipefd[WRITE_END]) == -1) {
        perror("Could not close write end of pipe (parent)");
        exit(-1);
    }
    if (kill(writer_pid, SIGTSTP) == -1) {
        perror("Could not send SIGTSTP to writer");
        exit(-1);
    }

    /*
     * Wait for child processes.
     */
    for (i = 0; i < NB_CHILDS; i++) {
        int ret;
        int status;

        while (wait(&status) == -1)
            ;
        if (WIFEXITED(status) != 0) {
            ret = WEXITSTATUS(status);
            printf("Child finished with status=%d\n", status);
        }
        if (ret != 0) {
            return_value = -1;
        }
    }
    return return_value;
}
