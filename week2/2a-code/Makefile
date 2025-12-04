CC ?= gcc
CFLAGS i?= -std=c2x -Wall -Wextra -Werror -pedantic

# A multiline string using \ to mark the continuation to the next line
PROGRAMS = \
    uint_le_to_uint_ascii \
    uint_be_to_uint_ascii \
    uint_le_to_uint_be \
    uint_be_to_uint_le \
    uint_ascii_to_uint_le \
    uint_ascii_to_uint_be \
    uint_ascii_to_uint_ascii \
    double_bin_to_double_ascii \
    double_ascii_to_double_ascii \
    double_ascii_to_double_bin \
    uint_le_to_double_bin \
    avg_doubles

build_num: numlib.c numlib.h
	gcc-15 $(CFLAGS) numlib.c -o numlib

num: build_num 
	./numlib

# all label makes it possible to call make without argument.
# calling 'make' is the same as calling 'make all'.
all: $(PROGRAMS)

build_test: numlib.c numlib.h
	gcc $(CFLAGS) numlib.c -o test_numlib 

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

avg_doubles: avg_doubles.c numlib.c double_ascii_to_double_bin.c
	gcc avg_doubles.c numlib.c double_ascii_to_double_bin.c -o avg_doubles 

test_functions: test_functions
	./test_functions