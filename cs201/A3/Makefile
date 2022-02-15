CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lm
PROGS=fp_parse

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(PROGS) *.o ~*
