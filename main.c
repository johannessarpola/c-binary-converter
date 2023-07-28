#include <stdio.h>
#include <string.h>
#include <math.h>

int convert_decimal(char *str) {
    size_t length = strlen(str);

    int total = 0;
    int j = length - 1;
    for (size_t i = 0; i < length; i++)
    {
        int one_or_zero = 0;
        if(str[i] == '1') {
            one_or_zero = 1;
        }

        int cur = one_or_zero * pow(2, j);
        total += cur;
        j--;
    }

    return total;
}
/*
Converts binary string to decimal
*/
int main(int argc, char *argv[]) {
    if(argc == 2 ) {
        int nbr = convert_decimal(argv[1]);
        printf("%d\n", nbr);
    }
    return 0;
}