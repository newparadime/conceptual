MAIN=bitFields

#CC=g++

SRC=$(MAIN).cpp
OBJ=$(SRC:.cpp=.o)

CFLAGS=-std=gnu11 -ggdb

.PHONY: default all clean

default: $(MAIN)

all: clean default

clean:
	$(RM) $(MAIN) $(OBJ)	

#$(MAIN): $(OBJ)
#	$(CC) $^ -o $@

#%.o: %.cpp
#	$(CC) -c $(CFLAGS) $^ -o $@
