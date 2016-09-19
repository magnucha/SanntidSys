XENO_DESTDIR:=
XENO_CONFIG:=$(XENO_DESTDIR)/usr/bin/xeno-config
XENO_CFLAGS:=$(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --skin native --cflags)
XENO_LIBS:=$(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --skin native --ldflags)

CC=gcc
CFLAGS=-g -pthread -D_GNU_SOURCE $(XENO_CFLAGS)
LDFLAGS= -g $(XENO_LIBS) -lcomedi -lrt -lm -pthread 
SOURCES=io.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=oving6


all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $^ $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<  

clean:
	rm *.o
