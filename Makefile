CFLAGS = -g -Wall -Wno-unused-parameter
CC = gcc

PROGRAMS = main

.PHONY: all clean

all: $(PROGRAMS)

main: main.o biblioLC.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $<

biblioLC.o: biblioLC.c
	$(CC) $(CFLAGS) -c $<

entreeSortieLC.o: entreeSortieLC.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o *.gch *~ $(PROGRAMS)