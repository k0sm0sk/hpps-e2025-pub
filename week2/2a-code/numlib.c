#include "numlib.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void skipspaces(FILE *f)
{
  while (1)
  {
    int c = fgetc(f);
    if (!isspace(c))
    {
      if (c != EOF)
      {
        ungetc(c, f);
      }
      return;
    }
  }
}

// // Read unsigned integer in base-10 ASCII format from the given file.
// // Stores the resulting number in the location pointed to by 'out'.
// // Stops at the first non-digit character, which is left unread. Returns nonzero
// // on failure. Fails if no digits are read before a non-digit is encountered.
// // Returns EOF if the first character read results in EOF.
int read_uint_ascii(FILE *f, uint32_t *out) {
  int read = 0;
  uint32_t num = 0;

  while (1) { //while 1 (true)

    int c = fgetc(f); // fgetc automatically advances filke pointer to next char, so basically an iterative loop through the file

    if (c >= '0' && c <= '9') { // check for ints (we are reading ints)
      num = num * 10 + (c - '0'); // 123 = 1*10^2 + 2*10^1 + 3*10^0
      /* we take the first number, move it the corresponding amount of places to the left (form decimal point)
      and add in the next number. So 
      c=1: '1' - '0' = 31 - 30 = 1, then 1 * 10^2 = 100  
      c=2: '2' - '0' = 32 - 30 = 2, then 100 + 2*10^1 = 100 + 20 = 120
      c=3: '3' - '0' = 33 - 30 = 3, then 120 + 3*10^0 = 120 + 3 = 123, and so '123' get's converted into int 123
      */
    }

    if (read == 0) { // if first digit we read
      if (c == EOF) { // if we reach EOF (end of file)
        return EOF;
      }
      else {
        read++; // if first digit but not EOF, keep while loop going
        // mistake in github solution, return 1 will keep on outputting 1 even though file contains other number
      }
    }
    else {
      *out = num; //bind value at memory address of out to be num
      return 0; // break
    }
    read++;
  }
}

// Write the provided integer in base-10 ASCII format to the given file. 
// Returns 0 on success.
int write_uint_ascii(FILE *f, uint32_t x) {
  if (f == NULL) { // we give as input the file f, but if our `FILE *f` pointer somehow is invalid (pointer had an error), we return error
    return 1;
  }
  char s[10]; // buffer to store ASCII version of number
  int i = 10; // start from end of buffer (last char written)

  while (x > 0) {
    int d = x % 10; // pick out last decimal digit
    x = x / 10; // remove last digit, 123 / 10 becomes 12.3, but since x is an unsigned 32-bit int (uint32_t), the decimal get's removed and so it becomes 12. (integer division, .3 is truncated)
    i = i - 1; // iterate up through the number (little endian so we go in "reverse")
    s[i] = '0' + d; // inverse of before, '0' + 1 = 40 + 1 = 41 = '1'
    if (x == 0) { // breaks when x becomes 0
      break;
    }
  }
  // pointer to start pos of string, size of written element (1), selects how many of the last slots of s[i] are used (for 123, i would be 7, so s[7], s[8] & s[9] would be used, and s[0] - s[6] are empty), last is file to write to.
  fwrite (&s[i], sizeof(char), 10-i, f);
  // assert(fclose(f) == 0); // returns 0 on success, fails assertion otherwise.
}

/*
Alternative solution from github

int write_uint_ascii(FILE *f, uint32_t x) {
  if (fprintf(f, "%u", x) < 0) {
    return 1;
  } else {
    return 0;
  }
}

*/


// * write_uint_le()
// Write the provided 32-bit integer in *little endian byte order*
// to the given file.  Returns 0 on success.
int write_uint_le(FILE *f, uint32_t x) {
  if (f == NULL) {
    return 1;
  }
  printf("\nWrite uint little endian, num: %d\n", x);
  /*
  unsinged char has single byte (8 bits), holds values 0 - 255 (128, 64, 32, ..., 1)
  *bytes declares pointer to the unsigned char. *bytes stores memory address of first byte of var x
  in other words, *bytes stores memory addresses of each bit of x. 42 has 4 addresses (32 bits = 4 bytes of 8 bits), which is accessed:
  0x0000002A (hex)
  00: 00000000, 00: 00000000, 00: 00000000, 2a (42): 00110010
  &x of course gets the memory address of x
  the (unsigned char *) is a type cast that makes the compiler treat the memory address as an unsigned char.
  We therefore make the compiler entrerpet the memory address as a sequence of individual bytes, allowing us to iterate through the values one by one.
  It could be viewed like this (random memory addresses):
  Address    Byte Value (Hex)    Binary Representation
  0x1000     0x2A               00101010  (LSB - least significant byte)
  0x1001     0x00               00000000
  0x1002     0x00               00000000
  0x1003     0x00               00000000  (MSB - most significant byte)

  And *no*, we can't just make a loop with stepsize 8 without type casting.
  If we do, we will be skipping parts of the uint32_t memory address, which wouldn't be converted correctly (like how 00000110 converted to 00 00 01 10 would be 1+2 instead of 4+2)
  */
  unsigned char *bytes = (unsigned char *)&x; 
  for (int i = 0; i < sizeof(x); i++)
  {
    if (fwrite(&bytes[i], sizeof(unsigned char), 1, f) != 1) { //fwrite requires pointer, so we use &bytes[i] so it writes the value at the address the pointer points at.
      return 1;
    }
    printf("i: %d,\t%hhx\n",i,bytes[i]);
  }

  return 0;
}





int main() {
  FILE *f = fopen("numtest.txt", "w"); // makes new file, if already made overwrites (truncates then writes)
  // if we want to check to see if the file exists, we can call read_uint_ascii (or just fopen with "r" instead), and check for != NULL, then do the "w".
  write_uint_ascii(f, 42);

  assert(fclose(f) == 0); // we need to close file first so we can reopen with "r". Alternatively "w+" followed by fflush(f); rewind(f);

  f = fopen("numtest.txt", "r");
  uint32_t value; //empty value we can output to with the *out

  read_uint_ascii(f, &value);
  printf("%d\n", value);
  assert(fclose(f) == 0);

  f = fopen("numtest.txt", "w");
  write_uint_le(f, 42); // ! we write binary to txt file, so we either need to be in correct cd and (macos) do xxd numtest.txt, or rename file to be of .bin (binary instead)
  // output of xxd numtest.txt: 00000000: 2a00 0000

  assert(fclose(f) == 0);

  return 0;
}