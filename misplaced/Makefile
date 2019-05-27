    MAIN=main

RM=rm -f
CC=g++

SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

CFLAGS=-std=gnu++17 -ggdb -Wall

.PHONY: default all clean

default: $(MAIN)

all: clean default

clean:
	$(RM) $(MAIN) $(OBJ)	

$(MAIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
