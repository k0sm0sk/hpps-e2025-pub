#include "numlib.h"
#include <stdio.h>

int main() {
    double value;
    
    while (read_double_ascii(stdin, &value) == 0) {
        write_double_bin(stdout, value);
    }
    
    return 0;
}
