CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-pthread
OFLAGS=-g -c

mt_rd: multithread_reader.o reader.o
	gcc $(CFLAGS) $(LFLAGS) -o mt_rd multithread_reader.o reader.o

multithread_reader.o: multithread_reader.c ../../Ex1/wrrd.h reader.h
	gcc $(CFLAGS) $(OFLAGS) multithread_reader.c

reader.o: reader.c ../../Ex1/wrrd.h reader.h
	gcc $(CFLAGS) $(OFLAGS) reader.c

clean:
	rm -f mt_rd *.o
