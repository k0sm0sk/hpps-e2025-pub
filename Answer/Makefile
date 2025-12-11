CFLAGS?=-std=c99 -Wall -Wextra -pedantic
CC?=cc

PROGRAMS=avg_doubles double_ascii_to_double_bin test_functions

all: $(PROGRAMS)

avg_doubles: avg_doubles.c numlib.c numlib.h
	$(CC) $(CFLAGS) avg_doubles.c numlib.c -o avg_doubles

double_ascii_to_double_bin: double_ascii_to_double_bin.c numlib.c numlib.h
	$(CC) $(CFLAGS) double_ascii_to_double_bin.c numlib.c -o double_ascii_to_double_bin

test_functions: test_functions.c numlib.c numlib.h
	$(CC) $(CFLAGS) test_functions.c numlib.c -o test_functions

clean:
	rm -f $(PROGRAMS) *.bin *.txt
