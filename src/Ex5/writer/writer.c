#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../../Ex1/wrrd.h"
#include "writer.h"

/*
 * This flag exists to guarantee that never occurs the situations when the writer
 * function tries to unlock the file it is writing to when it was never locked
 * or when it locks a file without unlocking it. If this flag did not exist, then
 * a SIGUSR2 signal between the lock and the unlock would cause the one of the above
 * situations to occur.
 */
static int file_locking = 1;


void* writer(void* arg) {
    char filename[FNLEN + 1];
    int  fd;
    int  line;

    char letter;
    char str[STRLEN + 1];
    char *str_to_write;

    char wrong_letter;
    char wrong_str[STRLEN + 1];
    int  wrong_letter_pos = 0;

    /*
     * O_WRONLY: Open the file so that it is write only.
     * O_CREAT:  If the file doesn't exist, create it.
     */
    int oflags = O_WRONLY | O_CREAT;

    /*
     * S_IRUSR: Set read rights for the owner to true.
     * S_IWUSR: Set write rights for the owner to true.
     * S_IROTH: Set read rights for other users to true.
     */
    int omodes = S_IRUSR | S_IWUSR | S_IROTH;

    (void)arg;

    /*
     * Set a seed for use by rand() inside getfile() and getstr().
     * See documentation in wrrd.h .
     */
    srand(time(NULL));

while (!get_finish_flag()) {
    getfile(filename, -1);

    /*
     * Open file.  Return if there was an error opening the file.
     */
    if ((fd = open(filename, oflags , omodes)) < 0) {
        perror("Error opening file");
        exit(-1);
    }

    if (get_file_locking()) {
        file_locking = 1;
        if (flock(fd, LOCK_EX) < 0) {
            perror("Error locking file");
            exit(-1);
        }
    }

    getstr(str);
    letter = str[0];
    strcpy(wrong_str, str);

    for (line = 0; line < STRNUM; line++) {
        str_to_write = str;

        /*
         * Produce an error every two lines.
         */
        if (get_error_writing() && (line % 2)) {
            wrong_letter = (double) rand() / (double) RAND_MAX * ('z' - 'a') + 'a';
            wrong_letter = (wrong_letter != letter) ? wrong_letter : wrong_letter + 1;
            wrong_letter_pos = rand() % (STRLEN - 1);
            wrong_str[wrong_letter_pos] = wrong_letter;
            str_to_write = wrong_str;
        }

        /*
         * Write to file. Return if number of bytes written is not
         * equal to the number of bytes to be written.
         */
        if (write(fd, str_to_write, STRLEN) != STRLEN) {
            perror("Error writing file");
            exit(-1);
        }

        wrong_str[wrong_letter_pos] = letter; /* correct the wrong string */
    }

    if (file_locking) {
        file_locking = 0;
        if (flock(fd, LOCK_UN) < 0) {
            perror("Error unlocking file");
            exit(-1);
        }
    }

    /*
     * Close file. Return upon failure to close.
     */
    if (close(fd) < 0) {
        perror("Error closing file");
        exit(-1);
    }
} /* while(1) */
    return 0;
}
