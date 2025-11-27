#include "numlib.h"
#include "assert.h"
#include "stdio.h"

void test_get_number(void) {
    assert(get_number() == 42);
}

int main(void) {
    test_get_number();
    printf("\nTest passed.\n");
    return 0;
}