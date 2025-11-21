#include <stdio.h>
#include "bitvec8.h"

struct test
{
    char name[20];
    int age;
};

bitvec8 bitvec8_from_int(unsigned int x)
{
    return 0xFF & x;
}

unsigned int bitvec8_to_int(bitvec8 v)
{
    return v;
}

void bitvec8_print(bitvec8 v)
{
    putchar('0' + ((v >> 7) & 1));
    putchar('0' + ((v >> 6) & 1));
    putchar('0' + ((v >> 5) & 1));
    putchar('0' + ((v >> 4) & 1));
    putchar('0' + ((v >> 3) & 1));
    putchar('0' + ((v >> 2) & 1));
    putchar('0' + ((v >> 1) & 1));
    putchar('0' + (v & 1));
}

int main() {
    // int like = 1;
    // printf("%p\n", &like);
    // printf("%i\n", like);

    // int *point;
    // point=&like;
    // int c=*point;

    // printf("%i\n", c);

    struct test testing={"Daniel", 22};
    printf("%s\n%d\n", testing.name, testing.age);
    int testing_age = testing.age;
    bitvec8 bit_age = bitvec8_from_int(testing_age);
    bitvec8_print(bit_age);
    printf("\n");
    bitvec8_print(~bit_age);
}
