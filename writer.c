/* writer.c */

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
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
	int fd = open("hello.txt", oflags , omodes);

	printf("after open\n");

	if (fd < 0)
	    return 1;

	printf("after open verification\n");

	while(j--)
	    if (write(fd, "hello\n", STRLEN) != STRLEN)
		return 1;

	printf("after write\n");

	if (close(fd) < 0)
	    return 1;

	printf("after close\n");
    }
    return 0;
}


char *getfile() {
    int r = rand() % 5;
    char *file = (char*)malloc(sizeof(char) * 13);
    char *filename = "SO2014-";
    char letter  = 'a' + r;
    char *ext = ".txt";

    strcpy(file, filename);
    strcat(file, &letter);
    strcat(file, ext);

    return file;
}

char *getstr() {
    int r = rand() % 10, i = 0;
    char *str = (char*)malloc(sizeof(char) * 12);
    char letter = 'a' + r;

    while(i++ < 10)
	str[i] = letter;

    str[i++] = '\n';
    str[i] = '\0';

    return str;
}
