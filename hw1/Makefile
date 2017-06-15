CC=gcc
CFLAGS=-I -Wall
DEPS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

maketiming: timing.o
	$(CC) -o timing timing.o $(CFLAGS)

clean:
	rm -f *.o core* *~ timing
