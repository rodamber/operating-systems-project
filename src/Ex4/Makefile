CFLAGS=-ansi -Wall -Wextra -pedantic

all: p_rd1

p_rd1: parallel_writer1.o
	gcc ${CFLAGS} -o p_rd1 paralell_writer1.o

parallel_writer1.o: parallel_writer1.c
	gcc ${CFLAGS} -c -g parallel_writer1.c

clean:
	rm -r *.o p_rd1

