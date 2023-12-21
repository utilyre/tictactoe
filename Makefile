CC=gcc
CFLAGS=-Wall -g -I.
LDLIBS=-lncurses

tictactoe: $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f tictactoe *.o
