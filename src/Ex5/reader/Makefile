CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-pthread
OFLAGS=-g -c

mt_rd: multithread_reader.o reader.o ex5_util.o
	gcc $(CFLAGS) $(LFLAGS) -o mt_rd multithread_reader.o reader.o ex5_util.o

multithread_reader.o: multithread_reader.c ../../Ex1/wrrd.h reader.h
	gcc $(CFLAGS) $(OFLAGS) multithread_reader.c

reader.o: reader.c ../../Ex1/wrrd.h reader.h
	gcc $(CFLAGS) $(OFLAGS) reader.c

ex5_util.o: ../util/ex5_util.c ../util/ex5_util.h
	gcc $(CFLAGS) $(OFLAGS) ../util/ex5_util.c

clean:
	rm -f mt_rd *.o
