all: wr rd

rd: reader.o wrrdaux.o
	gcc -o rd reader.o wrrdaux.o

wr: writer.o wrrdaux.o
	gcc -o wr writer.o wrrdaux.o

writer.o: writer.c wrrd.h
	gcc -c -g writer.c

reader.o: reader.c wrrd.h
	gcc -c -g reader.c

wrrdaux.o: wrrdaux.c wrrd.h
	gcc -c -g wrrdaux.c

clean:
	rm -f *.o wr rd
