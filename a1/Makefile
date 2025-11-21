CC?=cc 
CFLAGS?=-std=c11 -Wall -Werror -Wextra -pedantic

test: test_bitvec8.c bitvec8.c bitvec8.h
	gcc-15 $(CFLAGS) test_bitvec8.c bitvec8.c -o test_bitvec8 

run_test: test
	./test_bitvec8

learn: c_learning.c
	gcc-15 $(CLFAGS) c_learning.c -o learn

run_learn: learn
	./learn

clean: 
	rm -f guess
	rm -f roll
	rm -f test_bitvec8



