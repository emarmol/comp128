CC=gcc
CFLAGS=-I -Wall
DEPS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysproc: sysproc.o
	$(CC) -o sysproc sysproc.o $(CFLAGS)

clean:
	rm -f *.o core* *~ sysproc
