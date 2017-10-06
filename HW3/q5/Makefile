INCLUDE_DIRS =
LIB_DIRS =
CC=gcc

CDEFS=
CFLAGS=  -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

HFILES=
CFILES= first

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	 first

clean:
	-rm -f *.o *.d
	-rm -f first

first: first.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread -ldl -lm -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
