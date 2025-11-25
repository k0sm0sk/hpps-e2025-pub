#include "stdio.h"
#include "bitvec8.h"

bitvec8 bitvec8_from_int(unsigned int x) {
  return 0xFF & x;
}

unsigned int bitvec8_to_int(bitvec8 v) {
  return v;
}

void bitvec8_print(bitvec8 v) {
  putchar('0' + ((v>>7) & 1));
  putchar('0' + ((v>>6) & 1));
  putchar('0' + ((v>>5) & 1));
  putchar('0' + ((v>>4) & 1));
  putchar('0' + ((v>>3) & 1));
  putchar('0' + ((v>>2) & 1));
  putchar('0' + ((v>>1) & 1));
  putchar('0' + (v & 1));
}

struct add_result
{
  bitvec8 s;
  bitvec8 c;
};

struct add_result sum_and_carry(bitvec8 x, bitvec8 y) {
  struct add_result result;
    result.s = x ^ y;
    result.c = (x & y) << 1;
    return result;
}

bitvec8 bitvec8_add(bitvec8 x, bitvec8 y) {
  struct add_result r;

  r = sum_and_carry(x, y);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);
  r = sum_and_carry(r.s, r.c);

  return r.s;
}


bitvec8 bitvec8_negate(bitvec8 x) {
  return bitvec8_add(~x, bitvec8_from_int(1));
}
/*
  We had a lot of trouble with this part and had to read the book. Since bitvec8 type was defined with
  `typedef uint8_t bitvec8;`
  We can't use struct, and got a lot of errors. Instead we had to remove the struct given in the pdf 
  ```
  (Implement this function:
  struct bitvec8 bitvec8_negate ( struct bitvec8 x);)
  ```
  entirely
*/

bitvec8 bitvec8_mul(bitvec8 x, bitvec8 y) {
  bitvec8 result = 0;
  
  result = bitvec8_add(result, x & bitvec8_negate(y & 1));
  result = bitvec8_add(result, (x << 1) & bitvec8_negate((y >> 1) & 1));
  result = bitvec8_add(result, (x << 2) & bitvec8_negate((y >> 2) & 1));
  result = bitvec8_add(result, (x << 3) & bitvec8_negate((y >> 3) & 1));
  result = bitvec8_add(result, (x << 4) & bitvec8_negate((y >> 4) & 1));
  result = bitvec8_add(result, (x << 5) & bitvec8_negate((y >> 5) & 1));
  result = bitvec8_add(result, (x << 6) & bitvec8_negate((y >> 6) & 1));
  result = bitvec8_add(result, (x << 7) & bitvec8_negate((y >> 7) & 1));

  return result;
}
