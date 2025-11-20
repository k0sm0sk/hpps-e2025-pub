#include <stdio.h>
#include <string.h>

int main(int arg_amount, char *string_input[]) {
    if (arg_amount != 2) { // checks if 2 arguments are given
        printf("Incorrect amount of arguments, only 2 are accepted.\n");
        return 1; // false return
    }
    else {
        //  either a == x || a == y, or a == (x | y)
        if (string_input[1][0] == ('A' | 'a')) { // if first char of second argument (argument = makefile_command, input) == 'A' (for some reason "A" doesn't work)
            printf("No beginning A's are allowed.\n");
            return 1;
        }
        else {
            printf("%s\n", string_input[1]);
        }
    }
}
