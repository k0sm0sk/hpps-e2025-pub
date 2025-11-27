#include "numlib.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
// on failure. Fails if no digits are read before a non-digit is encountered.
// // Returns EOF if the first character read results in EOF.
int read_uint_ascii(FILE *f, uint32_t *out) {
  int read = 0;
  uint32_t num = 0;

  while (1) { //while 1 (true)

    int c = fgetc(f);

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
        return 1; // if first digit but not EOF, keep while loop going
      }
    }
    else {
      *out = num; //bind value at memory address of out to be num
      return 0; // break
    }
  }
}
