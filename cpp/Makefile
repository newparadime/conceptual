main=cpp

src=$(wildcard *.c)
obj=$(src:%.c=%.o)

CFLAGS=-ggdb -O3 -fPIC -Wall -Werror -pedantic

.PHONY: $(main) clean all

all: $(main)

$(main): $(obj)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
clean:
	$(RM) $(obj) $(objmain) $(libmain).a $(libmain).so $(binmain)
