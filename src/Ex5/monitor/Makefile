CFLAGS=-ansi -pedantic -Wall -Wextra
OFLAGS=-g -c

monitor: monitor.o ex5_util.o
	gcc $(CFLAGS) -o monitor monitor.o ex5_util.o

monitor.o: monitor.c ../../Ex1/wrrd.h ../util/ex5_util.h
	gcc $(CFLAGS) $(OFLAGS) -D_POSIX_C_SOURCE monitor.c

ex5_util.o: ../util/ex5_util.c ../util/ex5_util.h
	gcc $(CFLAGS) $(OFLAGS) ../util/ex5_util.c

clean:
	rm -f monitor *.o
