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

int main(int argc, char **argv) {
    int i, first = 1;
    uint32_t a, b, result;
    char *end;

    if (argc != 3) {
        wrapped_printf("Error: please provide two hexadecimal numbers as arguments to the program.\n");
        return -1;
    }

    a = strtol(argv[1], &end, 16);
    assert(end != NULL);
    b = strtol(argv[2], &end, 16);
    assert(end != NULL);

    result = a & b;
    if (result) {
        wrapped_printf("Bits ");
        for (i = 0; i < 32; ++i) {
            if (result >> i & 0x1) {
                if (first) {
                    wrapped_printf("%d", i);
                    first = 0;
                } else {
                    wrapped_printf(",%d", i);
                }
            }
        }

        wrapped_printf(" in common.  Hexadecimal: %x, Signed: %d, Unsigned: %u\n", result, result, result);
    } else {
        wrapped_printf("No bits in common.\n");
    }

    return 0;
}
