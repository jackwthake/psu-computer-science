#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
void print_binary(u_int16_t num) {
    int i = 0;
    for (i = 0; i < 16; ++i) {
        if (num >> i & 0x1) {
            wrapped_printf("1");
        } else {
            wrapped_printf("0");
        }
    }

    wrapped_printf("\n");
}

int main(int argc, char **argv) {
    u_int16_t result = 0x00;
    size_t i;

    if (argc < 2) { /* ensure there are arguments to be parsed */
        wrapped_printf("No input given.\n");
        return -1;
    }

    for (i = 1; i < argc; ++i) {
        char *end = NULL;
        u_int16_t arg = strtol(argv[i], &end, 10);
        
        if (arg > 15) {
            printf("Arguments must be in the range [0...15].\n");
            return -1;
        }

        result |= (uint16_t)0x01 << arg;
    }

    print_binary(result);
    return 0;
}
