CC ?= gcc
CFLAGS i?= -std=c2x -Wall -Wextra -Werror -pedantic

# A multiline string using \ to mark the continuation to the next line
PROGRAMS = hexabyte

build_hex: hexabyte.c
	gcc-15 $(CFLAGS) hexabyte.c -o hexabyte

run_hex: build_hex
	./hexabyte

build_num: numlib.c numlib.h
	gcc-15 $(CFLAGS) numlib.c numlib.h -o numlib

# all label makes it possible to call make without argument.
# calling 'make' is the same as calling 'make all'.
all: $(PROGRAMS)

build_test: numlib.c test_numlib.c numlib.h
	gcc-15 $(CFLAGS) numlib.c test_numlib.c -o test_numlib 

test: build_test
	./test_numlib

# % does pattern matching with the label name. The line below indicates that
# the dependencies are restricted to the C file of the same name as the label.
# $^ is the list of files in the dependencies.
# $@ is the label 
% : %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(PROGRAMS)
