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

void print_binary(uint16_t num) {
    int i;

    /* iterate through input, determine if there should be a 1 or 0 at a given position. */
    for (i = 15; i >= 0; --i) {
        if (num >> i & 0x1) {
            wrapped_printf("1");
        } else {
            wrapped_printf("0");
        }

        /* pretty print in spaces every 4 characters */
        if (i % 4 == 0 && i < 16) {
            wrapped_printf(" ");
        }
    }

    wrapped_printf("\n");
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


unsigned generate_bitmask(int offset, int mask_length) {
    unsigned mask = 0x00;
    for (int i = offset; i < mask_length + offset; ++i) { /* set a region of a string to 1 */
        mask |= (1 << i); /* set the current bit */
    }

    return mask;
}


void show_float(int f_bits, int e_bits, int bias, int num) {
    unsigned f_mask = generate_bitmask(0, f_bits);
    unsigned e_mask = generate_bitmask(f_bits, e_bits);
    unsigned fraction = f_mask & num, exponent = e_mask & num;
    int sign = num >> (f_bits + e_bits);

    print_binary(num);
    print_binary(fraction);
    print_binary(exponent);
    print_binary(sign);
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