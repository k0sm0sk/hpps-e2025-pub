#include "stdio.h"
#include "bitvec8.c"

int main(void) {
    printf("%d", bitvec8_to_int(bitvec8_add(bitvec8_from_int(4), bitvec8_from_int(6))));
    printf("\n");
    printf("%d", (bitvec8_from_int(4) + bitvec8_from_int(6)) & 0xFF);
    printf("\n");
    return 0;
}
