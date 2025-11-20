#include <stdio.h>
#include <stdint.h>

int main(int arg_amount, char *text[]) { // main(int of argument amount, array of pointers to char (0-indexed))
    if (arg_amount != 2) {
        printf("Wrong number of arguments\n");
        return 1; // 1 = false
    }

    else {
        for (int i=0; i<2; i++) {
            printf("%s\n", text[1]);
        }
    }
    return 0; // 0 = true
}
