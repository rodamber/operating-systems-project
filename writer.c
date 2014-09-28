/* writer.c */



#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <>
#include <>



int open_file(char* str);
int write_file(int fd, char* str);
char *get_file();
char *get_str();



int main(void) {

    int i = 5120;

    while(i--) {

	int j = 1024;
	int fd = open_file( get_file() );

	if (fd < 0)
	    return 1;

	while(j--)
	    write_file(fd, get_str());

	close_file(fd);
    }

    return 0;
}
