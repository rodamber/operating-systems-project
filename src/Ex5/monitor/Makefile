CFLAGS=-ansi -pedantic -Wall -Wextra
OFLAGS=-g -c

monitor: monitor.o
	gcc $(CFLAGS) -o monitor monitor.o

monitor.o: monitor.c ../../Ex1/wrrd.h
	gcc $(CFLAGS) $(OFLAGS) -D_POSIX_C_SOURCE monitor.c

clean:
	rm -f monitor *.o
