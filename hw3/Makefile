CC=gcc
CFLAGS=-I -Wall -lpthread
DEPS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wc: wc.o
	$(CC) -o wc wc.o $(CFLAGS)

clean:
	rm -f *.o core* *~ wc
