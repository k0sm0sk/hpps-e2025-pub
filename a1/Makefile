CC?=cc 
CFLAGS?=-std=c11 -Wall -Werror -Wextra -pedantic

build_test: test_bitvec8.c bitvec8.c bitvec8.h
	gcc-15 $(CFLAGS) test_bitvec8.c bitvec8.c -o test_bitvec8 

test: build_test
	./test_bitvec8


clean: 
	rm -f guess
	rm -f roll
	rm -f test_bitvec8



