CC?=cc 
CFLAGS?=-std=c11 -Wall -Werror -Wextra -pedantic

test: test_bitvec8.c bitvec8.c bitvec8.h
	gcc-15 $(CFLAGS) test_bitvec8.c bitvec8.c -o test_bitvec8 

test1: test.c
	gcc-15 $(CFLAGS) test.c -o test1

run_test: test
	./test_bitvec8

clean: 
	rm -f guess
	rm -f roll
	rm -f test_bitvec8



