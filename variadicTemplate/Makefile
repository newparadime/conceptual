MAIN=variadic

#CC=g++

C_SRC=$(wildcard *.c)
CXX_SRC=$(wildcard *.cpp)
OBJ=$(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)  

CFLAGS=-std=gnu11 -ggdb

.PHONY: default all clean

default: $(MAIN)

all: clean default

clean:
	$(RM) $(MAIN) $(OBJ)	

$(MAIN): $(OBJ)
	$(CXX) $(LDFLAGS) $(LD_LIBS) $^ -o $@

#%.o: %.cpp
#	$(CC) -c $(CFLAGS) $^ -o $@
