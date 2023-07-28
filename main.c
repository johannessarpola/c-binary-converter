#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool verbose = false;
const char *verboseF = "--verbose";
const char *verboseShortF = "-v";

int calculateExponent(const char *binaryString)
{
    int exponent = 0;
    int exponentBits = 11;
    int base = 1;

    char exponentPart[12];
    memcpy(exponentPart, binaryString, exponentBits + 1);

    if (verbose)
    {
        printf("Calculating the exponent part with array %s\n", exponentPart);
    }

    for (int i = exponentBits; i >= 1; i--)
    {
        if (exponentPart[i] == '1')
        {
            exponent += base;
        }
        base *= 2;

        if (verbose)
        {
            printf("base is %d\n", base);
        }
    }

    if (verbose)
    {
        printf("end exponent is %d\n", exponent);
    }
    return exponent;
}

double calculateFraction(const char *bstr, size_t length)
{
    double fraction = 0.0;
    double multiplier = 0.5;

    if (verbose)
    {
        printf("Calculating the fractional part with length %lu\n", length);
    }

    for (int i = 12; i < length; i++)
    {
        fraction += (bstr[i] - '0') * multiplier;

        if (verbose)
        {
            printf("bit     : %d\n", (bstr[i] - '0'));
            printf("iter    : %d\n", i);
            printf("fraction: %.10f\n", fraction);
            printf("mult    : %.10f\n", multiplier);
            printf("---\n");
        }

        multiplier *= 0.5;
    }

    return fraction;
}

double binaryStringToDouble(const char *bstr, size_t length)
{

    // Extract sign bit, -/+
    int sign = (bstr[0] == '1') ? -1 : 1;

    // Extract exponent bits and convert to an integer value
    int exponent = calculateExponent(bstr);

    // Extract fraction bits and convert to a fractional double value
    double fraction = calculateFraction(bstr, length);

    if (verbose)
    {
        printf("End components: \n");
        printf("Sign    :    %c\n", (bstr[0] == '1') ? '-' : '+');
        printf("Exponent:    %.10f\n", pow(2, exponent - 1023));
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
        return sign * (1.0 + fraction) * pow(2, exponent - 1023);
    }
}

// TODO Rework to be IEE 754 compliant
int convert_decimal(char *str, size_t length)
{

    int total = 0;
    int j = length - 1;
    for (size_t i = 0; i < length; i++)
    {
        int one_or_zero = 0;
        if (str[i] == '1')
        {
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
    if (length != 64)
    {
        // TODO Handle other than 64 bit double IEE754
        int nbr = convert_decimal(argv[1], length);
        printf("%d\n", nbr);
    }
    else
    {
        double nbr = binaryStringToDouble(argv[1], length);
        printf("%.5f\n", nbr);
    }

    return 0;
}