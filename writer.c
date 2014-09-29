/* writer.c */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "wrrd.h"


int main(void) {

    int i = TIMES_TO_CYCLE;

    while(i--) {

	char *fn  = (char*) malloc(sizeof(char) * (STRLEN + 1));
	char *str = (char*) malloc(sizeof(char) * (FNLEN + 1));
	int j = TIMES_TO_WRITE;
	
	/* 
	 * O_WRONLY: Write only.
	 * O_CREAT: If file doesn't exist, create it.
	 */
	int oflags = O_WRONLY | O_CREAT;

	/* 
	 * S_IRUSR: Set read rights for the owner to true. 
	 * S_IWUSR: Set write rights for the owner to true.
	 * S_IROTH: Set read rights for other users to true. 
	 */
	int omodes = S_IRUSR | S_IWUSR | S_IROTH;

	int fd; 		/* file descriptor */

	getfilename(fn);
	getstr(str);
	
	fd = open(fn, oflags , omodes);

	/* 
	 * Return if there was error opening the file.
	 */
	if (fd < 0)
	    return 1;

	free(fn);

	while(j--)
	    /*
	     * Return if number of bytes written is not equal to the number
	     * of bytes to be written.
	     */
	    if (write(fd, str, STRLEN) != STRLEN)
		return 1;

	free(str);

	/* Return upon failure to close. */
	if (close(fd) < 0)
	    return 1;
    }
    return 0;
}
