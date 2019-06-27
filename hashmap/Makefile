libmain=libhashmap
binmain=testhash

srcmain=$(binmain).c
objmain=$(srcmain:%.c=%.o)
src=$(filter-out $(srcmain), $(wildcard *.c))
obj=$(src:%.c=%.o)

ARFLAGS=ru
CFLAGS=-ggdb -O3 -fPIC -Wall -Werror -pedantic

LDLIBS=-l($(libmain).a)

.PHONY: $(libmain).a $(libmain).so $(binmain) clean all

all: $(libmain).a $(libmain).so $(binmain)

$(libmain).a: $(libmain).a($(obj))
	#$(AR) c $(ARFLAGS) $@ $%

$(libmain).so: $(obj)
	$(CC) -shared $(LDFLAGS) -o $@ $^

$(binmain): $(objmain)

clean:
	$(RM) $(obj) $(objmain)
