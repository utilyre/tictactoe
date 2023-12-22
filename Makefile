CC=gcc
CFLAGS=-I.
LDLIBS=-lncurses

release: CFLAGS+=-O3
release: target

debug: CFLAGS+=-Wall -g
debug: target

clean:
	rm -f target *.o

target: ncurext.o util.o main.o
	$(CC) ncurext.o util.o main.o -o target $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
