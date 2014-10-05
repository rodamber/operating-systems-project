/*
 * Identification
 *
 * 78294  José Semedo
 * 78471  João Marçal
 * 78942  Rodrigo Bernardo
 */

CFLAGS=-ansi -Wall -pedantic

all: wr rd

rd: reader.o wrrdaux.o
	gcc ${CFLAGS} -o rd reader.o wrrdaux.o

wr: writer.o wrrdaux.o
	gcc ${CFLAGS} -o wr writer.o wrrdaux.o

writer.o: writer.c wrrd.h
	gcc ${CFLAGS} -c -g writer.c

reader.o: reader.c wrrd.h
	gcc ${CFLAGS} -c -g reader.c

wrrdaux.o: wrrdaux.c wrrd.h
	gcc ${CFLAGS} -c -g wrrdaux.c

clean:
	rm -f *.o wr rd
