#include <stdio.h>
#include <assert.h>

int main(int arg_amount, char** argv)
{
    printf("\n");
    assert(arg_amount == 2);

    FILE *f = fopen(argv[1], "r");
    assert(f != NULL);
    
    char c;
    int i = 0;
    while (fread(&c, sizeof(char), 1, f) == 1) {
        printf("%.2x %2c\n", (int)c, c); // since c get's bounded to read the actual file, and not just open it, we use can call it as char to read each char, instead of the char converted to int.
        i++;
    }
    printf("\n");

}
