#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    else {
        for (int i=0; i<2; i++) {
            printf("%s\n", argv[1]);
        }
    }
    return 0;
}
