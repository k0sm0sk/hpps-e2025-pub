CC?=cc
CFLAGS?=-std=c11 -Wall -Werror -Wextra -pedantic

foo: foo.c
	gcc-15 -o foo foo.c $(CFLAGS)

mynameis: repeatme.c
	gcc-15 -o repeatme repeatme.c $(CFLAGS)

mynameis: mynameis.c
	gcc-15 -o mynameis mynameis.c $(CFLAGS)

guess: guess.c
	gcc-15 $(CFLAGS) guess.c -o guess

roll: roll.c
	gcc-15 $(CFLAGS) roll.c -o roll

test: test_bitvec8.c bitvec8.c bitvec8.h
	gcc-15 $(CFLAGS) test_bitvec8.c bitvec8.c -o test_bitvec8 

clean: 
	rm -f guess
	rm -f roll
	rm -f test_bitvec8
