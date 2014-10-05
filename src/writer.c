/*
 * Identification
 *
 * Group  24
 * 
 * 78294  José Semedo
 * 78471  João Marçal
 * 78942  Rodrigo Bernardo
 */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "wrrd.h"


int main(void) {

    int i = CYCLENUM;

    /*
     * Set a seed for use by rand() inside getfile() and getstr().
     * See documentation in wrrd.h .
     */
    srand(time(NULL));

    while (i--) {

	char filename[STRLEN + 1];
	char str[FNLEN + 1];
	int  strn = STRNUM;
	int  fdesc; 		/* file descriptor */
	
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

	getfile(filename);

	/* 
	 * Open file.  Return if there was an error opening the file.
	 */
	if ((fdesc = open(filename, oflags , omodes)) < 0) {
	    return -1;
	}

	getstr(str);

	while (strn--) {
	    /*
	     * Write to file. Return if number of bytes written is not
	     * equal to the number of bytes to be written.
	     */
	    if (write(fdesc, str, STRLEN) != STRLEN) {
		return -1;
	    }
	}

	/* 
	 * Close file. Return upon failure to close.
	 */
	if (close(fdesc) < 0) {
	    return -1;
	}
    }
    return 0;
}
