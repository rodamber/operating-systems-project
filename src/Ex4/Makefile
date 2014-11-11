CFLAGS=-ansi -Wall -Wextra -pedantic

all: p_rd1 wrrdaux.o p_rd2

p_rd1: parallel_reader1.o
	gcc ${CFLAGS} -o p_rd1 parallel_reader1.o

p_rd2: parallel_reader2.o ../Ex1/wrrd.h
	gcc ${CFLAGS} -o p_rd2 parallel_reader2.o wrrdaux.o

#p_rd3: parallel_reader3.o
#	gcc ${CFLAGS} -o p_rd3 parallel_reader3.o wrrdaux.o

parallel_reader1.o: parallel_reader1.c
	gcc ${CFLAGS} -c -g parallel_reader1.c

parallel_reader2.o: parallel_reader2.c ../Ex1/wrrd.h
	gcc ${CFLAGS} -c -g -lpthread parallel_reader2.c

#parallel_reader3.o: parallel_reader3.c ../Ex1/wrrd.h
#	gcc ${CFLAGS} -c -g -lpthread parallel_reader3.c

wrrdaux.o: ../Ex1/wrrdaux.c ../Ex1/wrrd.h
	gcc ${CFLAGS} -c -g ../Ex1/wrrdaux.c

clean:
	rm -f *.o p_rd1 p_rd2 #p_rd3

