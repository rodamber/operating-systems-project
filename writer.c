/* writer.c */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define TIMES_TO_CYCLE 5120	/* number of times the whole process on 
				   writer.c will be done */
#define TIMES_TO_WRITE 1024	/* number of strings that writer.c will
				   write*/
#define STRLEN 10		/* length of the strings to be written */



char *getfilename();
char *getstr();



int main(void) {

    int i = TIMES_TO_CYCLE;

    while(i--) {

	char *fn = getfilename();
	char *str = getstr();
	int j = TIMES_TO_WRITE;
	int oflags = O_WRONLY | O_CREAT;
	int omodes = S_IRUSR | S_IWUSR | S_IROTH;
	int fd = open(fn, oflags , omodes);

	if (fd < 0)
	    return 1;

	free(fn);

	while(j--)
	    if (write(fd, str, STRLEN + 1) != STRLEN + 1)
		return 1;

	free(str);

	if (close(fd) < 0)
	    return 1;
    }
    return 0;
}


char *getfilename() {
    int r = rand() % 5;
    char *file = (char*)malloc(sizeof(char) * 13);
    char *prefix = "SO2014-";
    char *number  = (char*)malloc(sizeof(char) * 2);
    char *ext = ".txt";

    number[0] = '0' + r;
    number[1] = '\0';

    strcpy(file, prefix);
    strcat(file, number);
    free(number);
    strcat(file, ext);

    return file;
}


char *getstr() {
    int  r = rand() % STRLEN, i = 0;
    char *str = (char*)malloc(sizeof(char) * (STRLEN + 1));
    char letter = 'a' + r;

    while(i++ < STRLEN - 1)
	str[i] = letter;

    str[i++] = '\n';
    str[i] = '\0';

    return str;
}
