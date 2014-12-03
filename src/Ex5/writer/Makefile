CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-pthread
OFLAGS=-g -c

mt_wr: multithread_writer.o writer.o wrrdaux.o
	gcc $(CFLAGS) $(LFLAGS) -o mt_wr multithread_writer.o writer.o wrrdaux.o

multithread_writer.o: multithread_writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) -D_POSIX_C_SOURCE multithread_writer.c

writer.o: writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) writer.c ../../Ex1/wrrdaux.c

wrrdaux.o: ../../Ex1/wrrdaux.c ../../Ex1/wrrd.h
	gcc $(CFLAGS) $(OFLAGS) ../../Ex1/wrrdaux.c

clean:
	rm -f mt_wr *.o
