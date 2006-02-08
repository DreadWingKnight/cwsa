SHELL = /bin/sh
SYSTEM = $(shell uname)
C++ = g++
DFLAGS =
OFLAGS = -O2 -w
LFLAGS = -L.
CFLAGS =

CFLAGS += $(OFLAGS) $(DFLAGS) -I.

OBJS = atom.o bencode.o main.o stringsplit.o util.o

PROGS = ./webseedadder

all: $(OBJS) $(PROGS)

./webseedadder: $(OBJS) 
	$(C++) -o ./bnbt $(OBJS) $(LFLAGS)

clean:
	rm -f $(OBJS) $(PROGS)

./webseedadder: $(OBJS) 

all: $(PROGS)

atom.o: atom.h
bencode.o: bencode.h atom.h
main.o: atom.h bencode.h util.h stringsplit.h WebSeedAdder_CPP_private.h
stringsplit.o: stringsplit.h 
util.o: util.h