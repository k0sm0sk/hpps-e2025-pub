#include "numlib.c"
#include "numlib.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[]){
    assert(argc >= 2);
    int i;
    for (i =0; i < argc; i++) {
        double value;
        FILE *f = fopen(argv[i], "r");
        read_double_bin(f,&value);
        assert(fclose(f) == 0);
    }
    return 0;
}