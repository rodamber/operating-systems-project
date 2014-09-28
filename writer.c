/* writer.c */



#include <fcntl.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "wrrd.h"


#define TIMES_TO_CYCLE 5120	/* number of times the whole process on writer.c
				   will be done */
#define TIMES_TO_WRITE 1024	/* number of strings that writer.c will write */
#define STRLEN 10		/* length of the strings to be written */



char *getfile();
char *getstr();



int main(void) {

    int i = TIMES_TO_CYCLE;

    while(i--) {

	int j = TIMES_TO_WRITE;
	int oflags = O_WRONLY || O_CREAT;
	int omodes = S_IRUSR || S_IWUSR || S_IROTH;
	int fd = open(getfile(), oflags , omodes);

	if (fd < 0)
	    return 1;

	while(j--)
	    if (write(fd, getstr(), STRLEN) != STRLEN)
		return 1;

	if (close(fd) < 0)
	    return 1;
    }
    return 0;
}


char *getfile() {
    char file[13] = "SO2014-";
    char *ext = ".txt";
    int r = rand() % 5;

    strcat(file, 'a' + r);
    strcat(file, ext);

    return file;
}

char *getstr() {
    int r = rand() % 10, i = 10;
    char str[11];
    char letter = 'a' + r;

    while(i--)
	str[i] = letter;

    return str;
}
