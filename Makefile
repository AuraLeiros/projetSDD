CFLAGS = -g -Wall -Wno-unused-parameter
CC = gcc

PROGRAMS = mainLC main

.PHONY: all clean

all: $(PROGRAMS)

mainLC: mainLC.o biblioLC.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $@ $^

mainLC.o: mainLC.c
	$(CC) $(CFLAGS) -c $<

biblioLC.o: biblioLC.c
	$(CC) $(CFLAGS) -c $<

entreeSortieLC.o: entreeSortieLC.c
	$(CC) $(CFLAGS) -c $<

main: main.o biblioH.o entreeSortieH.o
	$(CC) $(CFLAGS) -o $@ $^

biblioH.o: biblioH.c
	$(CC) $(CFLAGS) -c $<

entreeSortieH.o: entreeSortieH.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o *.gch *~ $(PROGRAMS)