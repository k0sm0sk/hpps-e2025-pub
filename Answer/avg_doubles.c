#include "numlib.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    double sum = 0.0;
    int count = 0;
    double value;
    
    // Read doubles from stdin until EOF
    while (read_double_bin(stdin, &value) == 0) {
        sum += value;
        count++;
    }
    
    if (count > 0) {
        printf("%f\n", sum / count);
    }
    
    return 0;
}
