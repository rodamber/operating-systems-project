CFLAGS=-ansi -pedantic -Wall -Wextra
LFLAGS=-pthread
OFLAGS=-g -c

main: parallel_reader.o reader.o
	gcc $(CFLAGS) $(LFLAGS) -o main parallel_reader.o reader.o

parallel_reader.o: parallel_reader.c ../../../Ex1/wrrd.h monitor.h
	gcc $(CFLAGS) $(OFLAGS) parallel_reader.c

reader.o: reader.c ../../../Ex1/wrrd.h monitor.h
	gcc $(CFLAGS) $(OFLAGS) reader.c

clean:
	rm main *.o
