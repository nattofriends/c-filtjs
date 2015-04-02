RM = rm -rf
CC = emcc
CFLAGS = -O2 --llvm-lto 1
EMCCFLAGS = -s INLINING_LIMIT=1 -s NO_EXIT_RUNTIME=1
EXPORTED_FUNCTIONS = ['_undname', '_demangle']

all: app/compiled.js

init:
	git submodule update --init

clean:
	$(RM) *.bc
	$(RM) undname.c
	$(RM) app/compiled.js

undname.c: init
	$(shell ./prepare-undname)

gcc/libiberty/cp-demangle.c: init

main.bc: main.c talloc/src/talloc.c
	$(CC) -o $@ $^ $(CFLAGS) -Iundname -Igcc/include -Italloc/src

undname.bc: undname.c
	$(CC) -o $@ $^ $(CFLAGS) -Iundname 

demangle.bc: gcc/libiberty/cp-demangle.c 
	$(CC) -o $@ $^ $(CFLAGS) -Igcc/include -DHAVE_STDLIB_H -DHAVE_STRING_H

app/compiled.js: main.bc undname.bc demangle.bc
	$(CC) -o $@ $^ $(CFLAGS) -s EXPORTED_FUNCTIONS="$(EXPORTED_FUNCTIONS)" $(EMCCFLAGS) --pre-js pre.js
