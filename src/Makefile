CC=gcc
CFLAGS=-Wall -O2

OBJ=main.o graph.o utils.o sptree.o

sptree: $(OBJ)
	$(CC) $(OBJ) -o sptree

main.o: main.c graph.h sptree.h
graph.o: graph.c graph.h utils.h
utils.o: utils.c utils.h
sptree.o: sptree.c sptree.h graph.h

clean:
	rm -f *.o sptree
