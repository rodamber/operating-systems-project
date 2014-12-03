CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-pthread
OFLAGS=-g -c

main: parallel_writer.o writer.o wrrdaux.o
	gcc $(CFLAGS) $(LFLAGS) -o main parallel_writer.o writer.o wrrdaux.o

parallel_writer.o: parallel_writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) -D_XOPEN_SOURCE parallel_writer.c

writer.o: writer.c ../../Ex1/wrrd.h writer.h
	gcc $(CFLAGS) $(OFLAGS) writer.c ../../Ex1/wrrdaux.c

wrrdaux.o: ../../Ex1/wrrdaux.c ../../Ex1/wrrd.h
	gcc $(CFLAGS) $(OFLAGS) ../../Ex1/wrrdaux.c

clean:
	rm main *.o
