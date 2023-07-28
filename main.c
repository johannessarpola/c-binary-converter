#include <stdio.h>
#include <string.h>
#include <math.h>

int calculateExponent(const char* binaryString) {
    int exponent = 0;
    int exponentBits = 11;
    int base = 1;

    for (int i = exponentBits; i >= 1; i--) {
        if (binaryString[i] == '1') {
            exponent += base;
        }
        base *= 2;
    }

    return exponent;
}


double calculateFraction(const char* bstr, size_t length) {
    double fraction = 0.0;
    double multiplier = 0.5;
    for (int i = 12; i < length; i++) {
        fraction += (bstr[i] - '0') * multiplier;
        multiplier *= 0.5;
    }

    return fraction;
}


double binaryStringToDouble(const char* bstr, size_t length) {

    // Extract sign bit, -/+
    int sign = (bstr[0] == '1') ? -1 : 1;

    // Extract exponent bits and convert to an integer value
    int exponent = calculateExponent(bstr);

    // Extract fraction bits and convert to a fractional double value
    double fraction = calculateFraction(bstr, length);

    // Handle special cases (zero, denormalized numbers)
    if (exponent == 0) {
        return sign * fraction * pow(2, -1022); // Denormalized numbers
    } else if (exponent == 2047) {
        return fraction != 0 ? NAN : sign * INFINITY; // Infinity or NaN
    }

    // Normalized numbers
    double result = sign * (1.0 + fraction) * pow(2, exponent - 1023);
    return result;
}

int convert_decimal(char *str, size_t length) {

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
        size_t length = strlen(argv[1]);
        if(length != 64) {
            int nbr = convert_decimal(argv[1], length);
            printf("%d\n", nbr);
        } else {
            double nbr = binaryStringToDouble(argv[1], length);
            printf("%.5f\n", nbr);
        }

    }
    return 0;
}