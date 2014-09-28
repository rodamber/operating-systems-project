# Makefile

wr: writer.o
	gcc -o wr writer.o

rd: reader.o
	gcc -o rd reader.o

writer.o: writer.c
	gcc -c -g writer.c

reader.o: reader.c
	gcc -c -g reader.c

clean:
	rm -f *.o wr rd
