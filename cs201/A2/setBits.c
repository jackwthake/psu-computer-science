#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
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

int main(int argc, char **argv) {
    uint16_t result = 0x00;
    size_t i;

    if (argc < 2) { /* ensure there are arguments to be parsed */
        wrapped_printf("No input given.\n");
        return -1;
    }

    /* iterate through the provided arguments */
    for (i = 1; i < argc; ++i) {
        char *end = NULL;
        uint16_t arg = strtol(argv[i], &end, 10);
        
        if (arg < 0 || arg > 15) { /* check provided argument */
            printf("Arguments must be in the range [0...15].\n");
            return -1;
        }

        /* set the apropriate bit */
        result |= (uint16_t)0x01 << arg;
    }

    print_binary(result);
    return 0;
}
