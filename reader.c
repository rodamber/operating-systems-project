#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "wrrd.h"


int main(void) {

    char fn[FNLEN + 1];
    char buf[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i = TIMES_TO_WRITE - 1, fd, n;

    getfilename(fn);

    /* 
     * Open file. Return if there was an error opening the file.
     */
    if ((fd = open(fn, O_RDONLY)) < 0)
	return EXIT_FAILURE;

    /* 
     * Read file. Return if there was an error reading the file. 
     */
    if ((read(fd, firstline, STRLEN)) < 0)
	return EXIT_FAILURE;

    firstline[STRLEN] = '\0';

    while (i--) {
	/* 
	 * Read file. Return if there was an error reading the file. 
	 */
	if (read(fd, buf, STRLEN) < 0)
	    return EXIT_FAILURE;

	buf[STRLEN] = '\0';

	/* 
	 * Return if not all lines are equal. 
	 */
	if (strcmp(buf, firstline))
	    return EXIT_FAILURE;
    }

    /* 
     * Return upon failure to close.
     */
    if (close(fd) < 0)	    
	return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}
