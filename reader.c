#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "wrrd.h"

#include <stdio.h>


int main(void) {
    int i = TIMES_TO_WRITE - 1; /*  */
    int fd; 			/* file descriptor */
    char *fn = (char*) malloc(sizeof(char) * (FNLEN + 1));
    char buf[STRLEN];
    char firstline[STRLEN];

    getfilename(fn);
    fd = open(fn, O_RDONLY);

    if(fd < 0) {	    
	printf("-1\n");
	return -1;
    }

    read(fd, firstline, STRLEN + 1);

    while(i--){	
	read(fd, buf, STRLEN + 1);
	printf("%s", buf);
	if(strcmp(buf, firstline) != 0) {
	    printf("0\n");
	    return 1;
	}
    }

    if(close(fd) < 0) {	    
	printf("-1\n");
	return 1;
    }
    
    printf("OK\n");
    return 0;
}
