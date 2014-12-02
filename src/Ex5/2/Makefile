CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-phtread
OFLAGS=-g -c

main: parallel_writer.o writer.o
	gcc $(CFLAGS) $(LFLAGS) -o main parallel_writer.o writer.o

parallel_writer.o: parallel_writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) parallel_writer.c

writer.o: writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) writer.c

clean:
	rm main *.o
