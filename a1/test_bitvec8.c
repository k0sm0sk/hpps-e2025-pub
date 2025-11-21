#include "bitvec8.h"
#include "assert.h"
#include "stdio.h"

void test_bitvec8_from_int(void) {
  assert(bitvec8_from_int(0xFF) == 255);
  assert(bitvec8_from_int(0x00) == 0);
  assert(bitvec8_from_int(0x100) == 0);
  assert(bitvec8_from_int(0x101) == 1);
  printf("Test %s passed!\n", __func__);
}


void bitvec_test_add(void) {
  assert(bitvec8_to_int(bitvec8_add(bitvec8_from_int(4), bitvec8_from_int(6))) == ((4 + 6) & 0xFF));
  assert(bitvec8_to_int(bitvec8_add(bitvec8_from_int(0), bitvec8_from_int(0))) == ((0 + 0) & 0xFF));
  assert(bitvec8_to_int(bitvec8_add(bitvec8_from_int(10), bitvec8_from_int(1))) == ((10 + 1) & 0xFF));
  printf("Test %s passed!\n", __func__);
}

void bitvec_test_negate(void) {
  printf("%d", bitvec8_to_int(bitvec8_from_int(-10)));
  printf("\n\n");
  printf("%d\n", bitvec8_to_int(bitvec8_negate(10)));
  assert(bitvec8_to_int(bitvec8_negate(bitvec8_from_int(10))) == bitvec8_to_int(bitvec8_from_int(-10)));
  printf("\nTest %s passed!\n", __func__);
}

void test_bitvec8_to_int(void) {
  assert(bitvec8_to_int(0xFF) == 255);
  assert(bitvec8_to_int(0x00) == 0);
  assert(bitvec8_to_int(0x01) == 1);
  printf("Test %s passed!\n", __func__);
}

void test_bitvec8_print(void) {
  printf("0xFF == ");
  bitvec8_print(0xFF);
  printf("\n");
  printf("0x00 == ");
  bitvec8_print(0x00);
  printf("\n");
  printf("0x01 == ");
  bitvec8_print(0x01);
  printf("\n");
  printf("0xEF == ");
  bitvec8_print(0xEF);
  printf("\n");
  printf("Test %s!\n", __func__);
}

int main(void) {
  test_bitvec8_from_int();
  test_bitvec8_to_int();
  test_bitvec8_print();
  bitvec_test_add();
  bitvec_test_negate();

  printf("All tests passed!\n");
  return 0;
  
}


