#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define EXPONENT_BIAS 1023

bool verbose = false;
const char *verboseF = "--verbose";
const char *verboseShortF = "-v";

int calculateExponent(const char *bstr, int exponentLength) // 12 on double
{
    int exponent = 0;
    int base = 1;

    if (verbose)
    {
        char exponentPart[exponentLength];
        memcpy(exponentPart, bstr, exponentLength + 1);
        printf("Calculating the exponent part with array %s\n", exponentPart);
    }


    for (int i = exponentLength; i >= 1; i--)
    {
        if (bstr[i] == '1')
        {
            exponent += base;
        }
        base *= 2;

        if (verbose)
        {
            printf("exponent: %d and base: %d\n", exponent, base);
        }
    }

    return exponent;
}

double calculateFraction(const char *bstr, size_t length, int exponentLength, int fractionLength)
{
    int skip = exponentLength + 1; // skip the sign and exponent

    if (verbose)
    {
        printf("Calculating the fractional part with length %lu\n", length);
    }


    double f = 0.0;
    int j = 0;
    for (int i = skip; i < length; i++)
    {
        // convert to int
        int bit = (bstr[i] - '0');

        // increasing j reduces the contirbution
        j++;
        // multiply bit by contributing factor and add to fraction
        f += bit / pow(2, j);

        if (verbose) {
            printf("bit         : %d\n", bit);
            printf("iter        : %d\n", j);
            printf("fraction    : %.10f\n", f);
            printf("contribution: %d/%.0f (2^%d)\n", bit, pow(2, j), j);
        }        
    }

    // Second way to do the same thing:

    // for (int i = skip; i < length; i++)
    // {
    //     //idiomatic way in c: converts a character representing a binary digit ('0' or '1') to its corresponding integer value (0 or 1).
    //     fraction += (bstr[i] - '0') * multiplier;

    //     if (verbose)
    //     {
    //         printf("bit     : %d\n", (bstr[i] - '0'));
    //         printf("iter    : %d\n", i);
    //         printf("fraction: %.10f\n", fraction);
    //         printf("mult    : %.10f\n", multiplier);
    //         printf("---\n");
    //     }

    //     multiplier *= 0.5;
    // }

    // return fraction;
    return f;
}

double binaryStringToDouble(const char *bstr, size_t length)
{

    // Extract sign bit, -/+
    int sign = (bstr[0] == '1') ? -1 : 1;

    // Extract exponent bits and convert to an integer value
    int exponent = calculateExponent(bstr, 11);

    // Extract fraction bits and convert to a fractional double value
    double fraction = calculateFraction(bstr, length, 11, 52);

    if (verbose)
    {
        printf("End components: \n");
        printf("Sign    :    %c\n", (bstr[0] == '1') ? '-' : '+');
        printf("Exponent:    %.f\n", pow(2, exponent - EXPONENT_BIAS));
        printf("Fraction:    %.10f\n", 1.0 + fraction);
    }

    // Handle special cases (zero, denormalized numbers)
    if (exponent == 0)
    {
        // Denormalized numbers
        return sign * fraction * pow(2, -1022);
    }
    else if (exponent == 2047)
    {
        // Infinity or NaN
        return fraction != 0 ? NAN : sign * INFINITY;
    }
    else
    {
        // Normalized numbers
        return sign * (1.0 + fraction) * pow(2, exponent - EXPONENT_BIAS);
    }
}

int convert_unsigned_int(const char *bstr, size_t length)
{

    int total = 0;
    int j = length - 1;
    for (size_t i = 0; i < length; i++)
    {
        // convert to int and multiply with pow
        int cur = (bstr[i] - '0') * pow(2, j);
        total += cur;
        j--;
    }

    return total;
}

/*
Converts binary string to decimal
*/
int main(int argc, char *argv[])
{
    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], verboseF) == 0 || strcmp(argv[i], verboseShortF) == 0)
        {
            printf("Using verbose\n");
            verbose = true;
        }
    }
    

    size_t length = strlen(argv[1]);
    char* s = argv[1];
    for (size_t i = 0; i < length; i++)
    {
        if(s[i] == '0' || s[i] == '1' ) {
            continue;
        } else {
            printf("Please use only binary strings");
            exit(1);
        }   
    }
    

    if (length != 64)
    {
        // TODO Handle other than 64 bit double IEE754
        int nbr = convert_unsigned_int(argv[1], length);
        printf("%d\n", nbr);
    }
    else
    {
        double nbr = binaryStringToDouble(argv[1], length);
        printf("%.5f\n", nbr);
    }

    return 0;
}