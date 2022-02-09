CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lm
PROGS=fp_parse

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*