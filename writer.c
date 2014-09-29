#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "wrrd.h"


int main(void) {

    int i = TIMES_TO_CYCLE;

    while(i--) {

	char fn[STRLEN + 1];
	char str[FNLEN + 1];
	int  j = TIMES_TO_WRITE, fd;
	
	/* 
	 * O_WRONLY: Write only.
	 * O_CREAT:  If file doesn't exist, create it.
	 */
	int oflags = O_WRONLY | O_CREAT;

	/* 
	 * S_IRUSR: Set read rights for the owner to true. 
	 * S_IWUSR: Set write rights for the owner to true.
	 * S_IROTH: Set read rights for other users to true. 
	 */
	int omodes = S_IRUSR | S_IWUSR | S_IROTH;

	getfilename(fn);

	/* 
	 * Open file.  Return if there was an error opening the file.
	 */
	if ((fd = open(fn, oflags , omodes)) < 0)
	    return EXIT_FAILURE;

	getstr(str);

	while (j--) {
	    /*
	     * Write to file. Return if number of bytes written is not
	     * equal to the number of bytes to be written.
	     */
	    if (write(fd, str, STRLEN) != STRLEN)
		return EXIT_FAILURE;
	}

	/* 
	 * Close file. Return upon failure to close.
	 */
	if (close(fd) < 0)
	    return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
