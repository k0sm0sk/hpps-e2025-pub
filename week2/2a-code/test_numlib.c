#include "numlib.h"
#include "assert.h"
#include "stdio.h"

void test_get_number(void) {
    printf("\n%d", get_number());
}

int main(void) {
    test_get_number();
    printf("\nTest passed.\n");
    return 0;
}