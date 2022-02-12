#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include <math.h>
#include <assert.h>

/* 
 * this function wraps the normal printf and error checks.
 * Variadic argument list from printf.c from:
 * https://code.woboq.org/userspace/glibc/stdio-common/printf.c.html
*/
void wrapped_printf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    assert(vprintf(fmt, args) > 0);
    va_end(args);
}

/* get the length of a binary string without leading zeroes */
int get_binary_length(int num) {
    int acc = 0, i;
    /* reconstruct binary, bit * 2^i stop when it adds up to the target, returning the number of bits in the number */
    for (i = 0; i < 16; ++i) { /* the largest possible bit string is 16 bits */
        acc += ((num >> i) & 0x1) * pow(2, i);

        if (acc == num)
            return i + 1;
    }

    return -1; /* an error occured if we reach here */
}


/* generate a bitmask covering a region of a bitstring */
unsigned generate_bitmask(int offset, int mask_length) {
    unsigned mask = 0x00, i;
    for (i = offset; i < mask_length + offset; ++i) { /* set a region of a string to 1 */
        mask |= (1 << i); /* set the current bit */
    }

    return mask;
}


/* get the fraction out of the binary string */
float get_fraction(unsigned fraction) {
    int length = get_binary_length(fraction), i, j;
    float acc = 0.0f;
    for (i = 0, j = length; i < length; ++i, --j) {
        if ((fraction >> i) & 0x1) {
            acc += pow(2, -j);
        }
    }

    return acc;
}


/* Show the IEEE 754 representation of the passed number with the specified number of bits */
void show_float(int f_bits, int e_bits, int bias, int num) {
    unsigned f_mask = generate_bitmask(0, f_bits), e_mask = generate_bitmask(f_bits, e_bits); /* bitmasks to isolate fields */
    unsigned fraction = f_mask & num, exponent = (e_mask & num) >> f_bits; /* isolate fields and shift appropriately */
    int sign = num >> (f_bits + e_bits), E, S;
    float M;

    if (exponent == generate_bitmask(0, e_bits)) { /* exponent is all 1's - Special values */
        if (fraction == 0x00) { /* either positive or negative infinity */
            if (sign) {
                wrapped_printf("-");
            } else {
                wrapped_printf("+");
            }

            wrapped_printf("inf\n");
        } else { /* exponent is 0 but fraction is not, results in NaN */
            wrapped_printf("NaN\n");
        }

        return;
    } else if (exponent == 0x00) /* exponent is all zeros - denormalized */{
        M = get_fraction(fraction);
        E = 1 - bias;
    } else { /* normalised */
        M = get_fraction(fraction) + 1;
        E = exponent - bias;
    }

    /* final calculation */
    S = pow(-1, sign);
    wrapped_printf("%f\n", S * M * pow(2, E));
}


int main(int argc, char **argv) {
    int f_bits = 0, e_bits = 0, num = 0x00, bias;
    int true_length = 0;
    
    if (argc != 4) {
        wrapped_printf("Not enough arguments supplied.\n");
        return EXIT_FAILURE;
    }

    /* grab command line arguments */
    assert(sscanf(argv[1], "%d", &f_bits) > 0);
    assert(sscanf(argv[2], "%d", &e_bits) > 0);
    assert(sscanf(argv[3], "%x", &num) > 0);

    /* bounds check sign bits */
    if ((f_bits < 2 || f_bits > 10) || (e_bits < 3 || e_bits > 5)) {
        wrapped_printf("Invalid argument\n");
        return EXIT_FAILURE;
    }

    /* checks that the inputted number can be represented within the inputted amount of bits, + 1 is for sign bit */
    true_length = get_binary_length(num);
    if (true_length <= 1 + e_bits + f_bits && true_length != -1) {
        bias = pow(2, e_bits - 1) - 1; /* from spec */
        show_float(f_bits, e_bits, bias, num);
    } else {
        wrapped_printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}