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

/*
 * Print the binary representation of a 16 bit unsigned integer
*/
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

void show_float(int fraction, int exponent, int bias, int num) {
    int E = 0;
    while (num) {
        ++E;
        num &= num - 1;
    }

    wrapped_printf("exp: %d, bias: %d\n", E + bias, bias);
}

int main(int argc, char **argv) {
    int fraction = 0, exponent = 0, num = 0x00, bias;
    
    if (argc != 4) {
        wrapped_printf("Not enough arguments supplied.\n");
        return EXIT_FAILURE;
    }

    assert(sscanf(argv[1], "%d", &fraction) > 0);
    assert(sscanf(argv[2], "%d", &exponent) > 0);
    assert(sscanf(argv[3], "%x", &num) > 0);

    if ((fraction < 2 || fraction > 10) || (exponent < 3 || exponent > 5)) {
        wrapped_printf("Invalid argument\n");
        return EXIT_FAILURE;
    }

    bias = pow(2, exponent - 1) - 1;
    show_float(fraction, exponent, bias, num);

    return EXIT_SUCCESS;
}