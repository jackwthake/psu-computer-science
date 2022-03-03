CC=gcc
CFLAGS=-std=gnu++11 -Wall -ansi
DFLAGS=-g
PROGS=a4
OBJS=menu.o

all: $(OBJS) $(PROGS)

a4: a4.c $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(OBJS)

menu.o: menu.c menu.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM