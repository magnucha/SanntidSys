CC=gcc
CFLAGS=-c -Wall -std=c99
LDFLAGS=
SOURCES=linked_list.c list_test.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=list_test

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o