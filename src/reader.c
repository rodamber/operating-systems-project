#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "wrrd.h"


int main(void) {

    char filename[FNLEN + 1];
    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  fdesc; 		/* file descriptor */
    int  strn;

    /*
     * Set a seed for use by rand() inside getfile().
     * See documentation in wrrd.h .
     */
    srand(time(NULL));

    getfile(filename);

    /*
     * Open file. Return if there was an error opening the file.
     * 
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
	return -1;
    }

    /* 
     * Read file. Return if there was an error reading the file. 
     */
    if ((read(fdesc, firstline, STRLEN)) < 0) {
	return -1;
    }

    firstline[STRLEN] = '\0';

    /*
     * First line must be composed of STRLEN - 1  equal chars between
     * 'a' and 'j', followed by a newline character, '\n'.
     */
    if (strlen(firstline) != STRLEN || firstline[0] < 'a'
	|| firstline[0] > 'j') {
 	return -1;
    }
    for (i = 1; i < STRLEN - 1; i++) {
	if (firstline[i] != firstline[0]) {
	    return -1;
	}
    }
    if (firstline[STRLEN - 1] != '\n') {
	return -1;
    }

    /*
     * Check if all lines are equal. Return if not.
     */
    for  (strn = 0; read(fdesc, line, STRLEN); strn++) {
	line[STRLEN] = '\0';

	if (strcmp(line, firstline)) {
	    return -1;
	}
    }

    /*
     * Return if there aren't STRNUM valid strings in the file or if there
     * was an error reading the file.
     */
    if (strn != STRNUM - 1) { /* -1 because the first line was already read */
	return -1;
    }

    /* 
     * Return upon failure to close.
     */
    if (close(fdesc) < 0) {
	return -1;
    }

    return 0;
}
