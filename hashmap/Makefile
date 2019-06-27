libmain=libhashmap
binmain=testhash

src=$(wildcard *.c)
obj=$(src:%.o=%.c)
srcmain=testhash.c
objmain=$(srcmain:%.o=%.c)

ARFLAGS=ru
CFLAGS=-ggdb -O3 -fPIC -Wall -Werror -pedantic

LDLIBS=-l($(libmain).a)

$(libmain).a: $(libmain)($(obj))
	$(AR) c $(ARFLAGS) $@ $%

$(libmain).so: $(obj)
	$(CC) -shared $(LDFLAGS) -o $@ $^

$(binmain): $(objmain)
