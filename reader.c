#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "wrrd.h"



int main(void) {
    int fd, i = TIMES_TO_WRITE - 1;
    char *fn = (char*) malloc(sizeof(char) * (FNLEN + 1));
    char buf[STRLEN + 1];
    char firstline[STRLEN + 1];

    getfilename(fn);
    fd = open(fn, O_RDONLY);

    free(fn);

    /* 
     * Return if there was error opening the file.
     */
    if(fd < 0)	    
	return -1;

    read(fd, firstline, STRLEN);

    firstline[STRLEN] = '\0';

    while(i--) {	

	read(fd, buf, STRLEN);
	buf[STRLEN] = '\0';

	if(strcmp(buf, firstline) != 0)
	    return 1;
    }

    /* 
     * Return upon failure to close.
     */
    if(close(fd) < 0)	    
	return 1;
    
    return 0;
}
