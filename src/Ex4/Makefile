CFLAGS=-ansi -Wall -Wextra -pedantic

all: p_rd1 parallel_reader2.o #p_rd2 p_rd3

p_rd1: parallel_reader1.o
	gcc ${CFLAGS} -o p_rd1 parallel_reader1.o

#p_rd2: parallel_reader2.o
#	gcc ${CFLAGS} -o p_rd2 parallel_reader2.o

#p_rd3: parallel_reader3.o
#	gcc ${CFLAGS} -o p_rd3 parallel_reader3.o

parallel_reader1.o: parallel_reader1.c
	gcc ${CFLAGS} -c -g parallel_reader1.c

parallel_reader2.o: parallel_reader2.c
	gcc ${CFLAGS} -c -g parallel_reader2.c

#parallel_reader3.o: parallel_reader3.c
#	gcc ${CFLAGS} -c -g parallel_reader3.c

clean:
	rm -f *.o p_rd1

