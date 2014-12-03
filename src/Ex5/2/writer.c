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


void* writer(void* arg) {
    char filename[FNLEN + 1];
    char letter;
    char str[STRLEN + 1];
    char wrong_letter;
    char wrong_str[STRLEN + 1];
    char *str_to_write;
    int  line;
    int  fdesc;         /* file descriptor */

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

while (1) {
    if (get_finish_flag()) {
        exit(0);
    }

    getfile(filename, -1);

    /*
     * Open file.  Return if there was an error opening the file.
     */
    if ((fdesc = open(filename, oflags , omodes)) < 0) {
        perror("Error opening file");
        exit(-1);
    }

    if (flock(fdesc, LOCK_EX) < 0) {
        perror("Error locking file");
        exit(-1);
    }

    getstr(str);
    letter = str[0];

    for (line = 0; line < STRNUM; line++) {
        strcpy(wrong_str, str);
        str_to_write = str;

        if (get_error_writing() && (line % 2)) {
            wrong_letter = (double) rand() / (double) RAND_MAX * ('z' - 'a') + 'a';
            wrong_letter = (wrong_letter != letter) ? wrong_letter : wrong_letter + 1;
            wrong_str[rand() % (STRLEN - 1)] = wrong_letter;
            str_to_write = wrong_str;
        }

        /*
         * Write to file. Return if number of bytes written is not
         * equal to the number of bytes to be written.
         */
        if (write(fdesc, str_to_write, STRLEN) != STRLEN) {
            perror("Error writing file");
            exit(-1);
        }
    }

    if (flock(fdesc, LOCK_UN) < 0) {
        perror("Error unlocking file");
        exit(-1);
    }

    /*
     * Close file. Return upon failure to close.
     */
    if (close(fdesc) < 0) {
        perror("Error closing file");
        exit(-1);
    }
} /* while(1) */
}
