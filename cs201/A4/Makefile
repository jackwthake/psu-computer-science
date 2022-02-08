CC=gcc
CFLAGS=-Wall -ansi
DFLAGS=-g
PROGS= setBits showBits

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*