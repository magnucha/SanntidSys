CC=gcc
CFLAGS=-c -std=c99 -pthread
LDFLAGS=-lcomedi -lrt -lm -pthread 
SOURCES=io.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=oving5

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o